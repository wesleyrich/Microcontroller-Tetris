/*
 * audio.c
 *
 *  Created on: Nov 15, 2019
 *      Author: rich27
 */
#include "stm32f0xx.h"
#include "stm32f0_discovery.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "audio.h"
#define RATE 100000
#define N 1000
short int wavetable[N];


void init_wavetable(void)
{
  int x;
  for(x=0; x<N; x++)
    wavetable[x] = 32767 * sin(2 * M_PI * x / N);
}

float stan_1[7] = {B5,C6s,D6,E6,F6s,D6,F6s};
//static const uint8_t stan_1[7] = {B5,C6s,D6,E6,F6s,D6,F6s};
float stan_2[6] = {F6,C6s,F6,E6,C6,E6};
float stan_3[8] = {B5,C6s,D6,E6,F6s,D6,F6s,B6};
float stan_4 [6]= {A6,F6s,D6,F6s,A6,A6};
//then go back to stan_1 and stan_2 and stan_3
float stan_8[6] = {A6,F6s,D6,C6s,B6,B6};
//go down to 3 octave
float stan_9[7] = {B3,C4s,D4,E4,F4s,F4,D4s};
float stan_10[6] = {F4,C4s,F4,E4,C4,E4};
float stan_11[8] = {B3,C4s,D4,E4,F4s,D4,F4s,B4};
float stan_12[6]= {A4,F4s,D4,F4s,A4,A4};
//repeat stan9 stan10 stan11 stan12

float stan_13[7] = {F4s,G4s,A4s,B4,C5s,A4,C5s};
float stan_14[6] = {D5,A4s,D5,C5,A4s,C5};
//repeat stan_13
float stan_15[5] = {D5,A4s,D5,C5,C5};
//https://pages.mtu.edu/~suits/notefreqs.html

float * stanzas[31] = {stan_1,stan_2,stan_3,stan_4,stan_1,stan_2,stan_3,stan_8,stan_9,stan_10,stan_11,stan_12,stan_9,stan_10,stan_11,stan_12,stan_13,stan_14,stan_13,stan_15,stan_13,stan_14,stan_13,stan_15,stan_9,stan_10,stan_11,stan_12,stan_9,stan_10,stan_11,stan_12};

int offset = 0;
int step = B5 * N / RATE * (1 << 16);

void setup_gpio() {
    /* Student code goes here */
    RCC -> AHBENR |= RCC_AHBENR_GPIOBEN;
    GPIOB ->MODER &= GPIO_MODER_MODER4;
    GPIOB ->MODER |= GPIO_MODER_MODER4;

}

void setup_dac() {
    RCC -> APB1ENR |= RCC_APB1ENR_DACEN;
    DAC ->CR &= ~DAC_CR_EN1;
    DAC ->CR &= ~DAC_CR_BOFF1;
    DAC ->CR |= DAC_CR_TEN1;
    DAC ->CR |= DAC_CR_TSEL1;
    DAC ->CR |= DAC_CR_EN1;
    /* Student code goes here */
}

void setup_timer6() {

    RCC -> APB1ENR |= RCC_APB1ENR_TIM6EN;
    TIM6 -> PSC = 10-1;
    TIM6 -> ARR = 48-1;
    TIM6 -> CR1 |= TIM_CR1_CEN;
    TIM6 -> DIER |= TIM_DIER_UIE;

    NVIC -> ISER[0] = 1<<TIM6_DAC_IRQn;

    /* Student code goes here */
}

void setup_adc() {
    /* Student code goes here */
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    RCC->CR2 |= RCC_CR2_HSI14ON;
    while(!(RCC->CR2 & RCC_CR2_HSI14RDY));
    ADC1->CR |= ADC_CR_ADEN;
    while(!(ADC1->ISR & ADC_ISR_ADRDY));



}

//https://musescore.com/torbybrand/in-the-hall-of-the-mountain-king

void TIM6_DAC_IRQHandler() {
    DAC->SWTRIGR |= DAC_SWTRIGR_SWTRIG1;
       TIM6->SR &= ~TIM_SR_UIF;

       offset += step;
       if ((offset>>16) >= N)
       {
           offset -= N<<16;
       }
   int sample = wavetable[offset>>16];
   sample = sample /16 + 2048;
   DAC->DHR12R1 = sample;
}

void test_audio(){
    setup_gpio();
      setup_dac();
      init_wavetable();
      setup_timer6();
}
int iter = 0;
int measure = 0;
void update_note()
{
    offset = 0;
    step = stanzas[measure][iter] * N / RATE * (1 << 16);
    iter++;
    if (iter > sizeof stanzas[measure] / sizeof stanzas[measure][0])
    {
        iter = 0;
        measure++;
    }
    if (measure > 31)
    {
        measure = 0;
        iter = 0;
    }
}


