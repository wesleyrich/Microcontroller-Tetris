/*
 * led_matrix.c
 *
 *  Created on: Oct 30, 2019
 *      Author: Grant, Wesley, Not really Daryl yet
 */

#include "stm32f0xx.h"
#include "stm32f0_discovery.h"

#define LED_OE 0
#define LED_CLK 1
#define LED_C 2
#define LED_A 3
#define LED_B2 4
#define LED_R2 5
#define LED_B1 6
#define LED_R1 7
#define LED_LAT 8
#define LED_D 9
#define LED_B 10
#define LED_G2 11
#define LED_G1 12

void set_bit_c(int code, int state);
void set_row(int row);
void update_led();

void LED_pins_setup ()
{
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN; 	// enable clock to GPIOA
	// set pins 0-12 for output
	GPIOC->MODER &= ~(0x3ffffff);
	GPIOC->MODER |= (0x1555555);
	set_bit_c(LED_B1, 1);
	set_bit_c(LED_G2, 1);
	set_bit_c(LED_A, 1);
	set_bit_c(LED_OE, 0);
	set_bit_c(LED_CLK, 1);
}

void tim2_setup ()
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; // enable clock to tim6

	// set up the clock frequency
	TIM2->ARR = 9;
	TIM2->PSC = 23;

	TIM2->DIER |= TIM_DIER_UIE; 		// enable the update interrupt
	TIM2->CR1 |= TIM_CR1_CEN; 			// enable the timer counter
	NVIC->ISER[0] = 1 << TIM2_IRQn; // enable the interrupt
}

void TIM2_IRQHandler ()
{
	TIM2->SR &= ~TIM_SR_UIF; // acknowledge the interrupt
	update_led();
}

// Sets a bit in GPIOC based on state. State must be 0 or 1
void set_bit_c(int code, int state)
{
	if(state == 1)
	{
		GPIOC->BSRR = 1 << code;
	}
	else if(state == 0)
	{
		GPIOC->BSRR = 1 << (code + 16);
	}
	else //infinitely looping
	{
		for(;;);
	}
}

int counter = 0;
int row_count = 0;
void update_led()
{
	if (counter == 2) // if finished with row
	{
		set_bit_c(LED_OE, 0);
		set_row(row_count);
		set_bit_c(LED_LAT, 1); // turn on latch (LAT)
		counter = 0;
		if(row_count > 15) row_count = 0;
		else row_count++;
		return;
	}
	if (counter == 0)
	{
		set_bit_c(LED_OE, 1);
		set_bit_c(LED_LAT, 0); // turn off latch (LAT)
	}

	if((GPIOC->ODR & 1 << LED_CLK) == 1 << LED_CLK) GPIOC->ODR ^= 1 << LED_B1;
	GPIOC->ODR ^= 1 << LED_CLK; // toggle CLK
	counter++;
}

void set_row(int row)
{
	if (row % 2 == 0)
	{
		set_bit_c(LED_A, 0);
	}
	else
	{
		set_bit_c(LED_A, 1);
	}
	row /= 2;
	if (row % 2 == 0)
	{
		set_bit_c(LED_B, 0);
	}
	else
	{
		set_bit_c(LED_B, 1);
	}
	row /= 2;
	if (row % 2 == 0)
	{
		set_bit_c(LED_C, 0);
	}
	else
	{
		set_bit_c(LED_C, 1);
	}
	row /= 2;
	if (row % 2 == 0)
	{
		set_bit_c(LED_D, 0);
	}
	else
	{
		set_bit_c(LED_D, 1);
	}
}

//void set_color( color)
//{
//	/* COLOR LIST
//	 * 0 -> RED
//	 *
//	 */
//}
