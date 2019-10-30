/*
 * led_matrix.c
 *
 *  Created on: Oct 30, 2019
 *      Author: Grant
 */

#include "stm32f0xx.h"
#include "stm32f0_discovery.h"

#define LED_OE = 0;
#define LED_CLK = 1;
#define LED_C = 2;
#define LED_A = 3;
#define LED_B2 = 4;
#define LED_R2 = 5;
#define LED_B1 = 6;
#define LED_R1 = 7;
#define LED_LAT = 8;
#define LED_D = 9;
#define LED_B = 10;
#define LED_G2 = 11;
#define LED_G1 = 12;

void LED_pins_setup ()
{
	/*
	LED has pins R1 B1 R2 B2 A C CLK OE G1 G2 B D LAT
	only really need R1, CLK OE and LAT to display something
	~FOR NOW~
	PC0 = OE
	PC1 = CLK
	PC2 = C
	PC3 = A
	PC4 = B2
	PC5 = R2
	PC6 = B1
	PC7 = R1
	PC8 = LAT
	PC9 = D
	PC10 = B
	PC11 = G2
	PC12 = G1
	*/

	RCC->AHBENR |= RCC_AHBENR_GPIOAEN; 	// enable clock to GPIOA

	// set pins 0 1 2 3 for output
	GPIOC->MODER &= ~(0x3ffffff);
	GPIOC->MODER |= (0x1555555);
	// set R1 / OE to high
	GPIOC->ODR |= GPIO_ODR_3 | GPIO_ODR_2;

}

void tim6_setup ()
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN; // enable clock to tim6

	// set up the clock frequency
	TIM6->ARR = 8 - 1;
	TIM6->PSC = 4 - 1;

	TIM6->DIER |= TIM_DIER_UIE; 		// enable the update interrupt
	TIM6->CR1 |= TIM_CR1_CEN; 			// enable the timer counter
	NVIC->ISER[0] = 1 << TIM6_DAC_IRQn; // enable the interrupt
}

void TIM6_DAC_IRQHandler ()
{
	TIM6->SR &= ~TIM_SR_UIF; // acknowledge the interrupt
	update_led();
}

int counter = 0;

void update_led()
{
	if (counter == 32) // if finished with row
	{
		GPIOA->ODR |= GPIO_Pin_1 | GPIO_Pin_0; // turn on latch (LAT)
		counter = 0;
		return;
	}
	if (counter == 0)
	{
		GPIOA->ODR &= ~(GPIO_Pin_1 | GPIO_Pin_2); // turn off latch (LAT)
	}
	GPIOA->ODR ^= GPIO_Pin_0; // toggle CLK

	counter++;
}
