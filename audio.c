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
#define RATE 100000
#define N 1000
short int wavetable[N];
uint8_t stanzas[31] = {stan_1,stan_2,stan_3,stan_4,stan_1,stan_2,stan_3,stan_8,stan_9,stan_10,stan_11,stan_12,stan_9,stan_10,stan_11,stan_12,stan_13,stan_14,stan_13,stan_15,
        stan_13,stan_14,stan_13,stan_15,stan_9,stan_10,stan_11,stan_12,stan_9,stan_10,stan_11,stan_12};

void init_wavetable(void)
{
  int x;
  for(x=0; x<N; x++)
    wavetable[x] = 32767 * sin(2 * M_PI * x / N);
}


void setup_gpio() {
    /* Student code goes here */
    RCC -> AHBENR |= RCC_AHBENR_GPIOAEN;
    GPIOA ->MODER &= ~0x33F;
    GPIOA ->MODER |= 0x33F;

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
    // Student code goes here...
}

void test_audio(){
    setup_gpio();
      setup_dac();
      init_wavetable();
      setup_timer6();
      for(int i = 0; i<= 31; i++)
      {
          int stan_value = stansaz[i];
          stan_value[]
      }

      step = freq * N / 100000.0 * (1 << 16);
}
}

