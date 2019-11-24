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
	  wavetable[x] = (32767 * sin(x * 2 * M_PI / N) +32768)/16;
}

//133 notes

float mountain_king[] = {B3,C4s,D4,E4,F4s,D4,F4s,0,F4,C4s,F4,0,E4,C4,E4,0,
                         B3,C4s,D4,E4,F4s,D4,F4s,B4,A4,F4s,D4,F4s,A4,A4,0,0, // repeat
						 B3,C4s,D4,E4,F4s,D4,F4s,0,F4,C4s,F4,0,E4,C4,E4,0,
						 B3,C4s,D4,E4,F4s,D4,F4s,B4,A4,F4s,D4,F4s,A4,A4,0,0,  // move up a fifth
						 F4s,G4s,A4s,B4,C5s,A4s,C5s,0,D5,A4s,D5,0,C5s,A4s,C5s,0,
						 F4s,G4s,A4s,B4,C5s,A4s,C5s,0,D5,A4s,D5,0,C5s,C5s,C5s,0,  // repeat
						 F4s,G4s,A4s,B4,C5s,A4s,C5s,0,D5,A4s,D5,0,C5s,A4s,C5s,0,
						 F4s,G4s,A4s,B4,C5s,A4s,C5s,0,D5,A4s,D5,0,C5s,C5s,C5s,0,  // move up the rest of octave
						 B4,C5s,D5,E5,F5s,D5,F5s,0,F5,C5s,F5,0,E5,C5,E5,0,
						 B4,C5s,D5,E5,F5s,D5,F5s,B5,A5,F5s,D5,F5s,A5,A5,0,0};

float rickroll[] = {C5s,C5s,C5s,C5s,C5s,C5s,D5s,D5s,D5s,D5s,D5s,D5s,G4s,G4s,G4s,G4s,D5s,D5s,D5s,D5s,D5s,D5s,F5,F5,F5,F5,F5,F5,
                    G5s,F5s,F5,C5s,C5s,C5s,D5s,D5s,D5s,G4s,G4s,G4s,G4s,G4s,G4s,G4s,C5s,D5s,
                    C5s,C5s,C5s,D5s,D5s,D5s,G4s,G4s,D5s,D5s,D5s,F5,F5,F5,
                    G5s,F5s,F5,C5s,C5s,C5s,D5s,D5s,D5s,G4s,G4s,G4s,G4s,G4s,G4s,C5s,G4s,C5s,
                    A4s,C5,C5s,C5s,D5s,C5,C5,A4s,G4s,G4s,G4s,G4s,G4s,G4s,0,
                    A4s,A4s,C5,C5s,A4s,0,G4s,G5s,0,G5s,D5s,D5s,D5s,D5s,D5s};

float celebrate[] = {};

int offset = 0;
int step = B5 * N / RATE * (1 << 16);


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
//    DAC->SWTRIGR |= DAC_SWTRIGR_SWTRIG1;
//       TIM6->SR &= ~TIM_SR_UIF;
//
//       offset += step;
//       if ((offset>>16) >= N)
//       {
//           offset -= N<<16;
//       }
//   int sample = wavetable[offset>>16];
//   sample = sample /16 + 2048;
//   DAC->DHR12R1 = sample;
}

void test_audio(){
      setup_dac();
      init_wavetable();
      setup_dma();
	  reint_timer();
      //setup_timer6();
}
int iter = 0;
//int measure = 0;
void update_note()
{

//    offset = 0;
//    step = music[iter] * N / RATE * (1 << 16);
//    iter++;
//        if (iter > sizeof music / sizeof music[0])
//        {
//            iter = 0;
//        }

	TIM15->PSC = freq_to_psc(mountain_king[iter]);
	iter++;
	if (iter > sizeof mountain_king / sizeof mountain_king[0])
	{
		iter = 0;
	}
}

void setup_dma(){
	RCC -> AHBENR |= RCC_AHBENR_DMA1EN;
	    DMA1_Channel5 -> CCR &= ~(DMA_CCR_EN);
	    DMA1_Channel5 -> CMAR = (uint32_t) (wavetable);
	    DMA1_Channel5 -> CPAR = (uint32_t) &(DAC->DHR12R1);
	    DMA1_Channel5 -> CNDTR = N;
	    DMA1_Channel5 -> CCR &= ~(DMA_CCR_MSIZE |DMA_CCR_PSIZE);
	    DMA1_Channel5 -> CCR |= DMA_CCR_MSIZE_0 | DMA_CCR_PSIZE_0;
	    DMA1_Channel5 -> CCR  &= ~(DMA_CCR_MEM2MEM);
	    DMA1_Channel5 -> CCR |= DMA_CCR_MINC | DMA_CCR_CIRC | DMA_CCR_DIR;
	    DMA1_Channel5 -> CCR |= DMA_CCR_EN;

}

void reint_timer()
{
 RCC -> APB2ENR |= RCC_APB2ENR_TIM15EN;
 TIM15 -> CR1 &= ~(TIM_CR1_CEN);
 TIM15 -> PSC = 27 - 1;
 TIM15 -> ARR = 2 - 1;
 TIM15 -> CR2 &= ~(TIM_CR2_MMS);
 TIM15 -> CR2 |= TIM_CR2_MMS_1;
 TIM15 -> DIER |= TIM_DIER_UDE;
 TIM15 -> CR1 |= TIM_CR1_CEN;

 RCC -> APB1ENR |= RCC_APB1ENR_DACEN;
 DAC -> CR &= ~(DAC_CR_TSEL1);
 DAC -> CR |= DAC_CR_TSEL1_1 | DAC_CR_TSEL1_0;
 DAC -> CR |= DAC_CR_TEN1;
 //DAC -> CR |= DAC_CR_EN1;


}

int freq_to_psc(float freq)
{
	return (int)((float)(24000.0) / freq) - 1;
}

