/*
 * led_matrix.c
 *
 *  Created on: Oct 30, 2019
 *      Author: Grant, Wesley, Daryl
 */

#include "stm32f0xx.h"
#include "stm32f0_discovery.h"

// PIN NUMBERS IN GPIOC
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

// COLORS
#define C_OFF -1
#define C_R 0
#define C_B 1
#define C_G 2
#define C_RB 3
#define C_RG 4
#define C_GB 5
#define C_RGB 6

void set_bit_c(int code, int state);
void set_row(int row);
void update_led();
void set_color(int channel, int color);
void nano_wait(unsigned int n);

void nano_wait(unsigned int n) {
    asm(    "        mov r0,%0\n"
            "repeat: sub r0,#83\n"
            "        bgt repeat\n" : : "r"(n) : "r0", "cc");
}

void LED_pins_setup ()
{
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN; 	// enable clock to GPIOA
	// set pins 0-12 for output
	GPIOC->MODER &= ~(0x3ffffff);
	GPIOC->MODER |= (0x1555555);
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
	nano_wait(100000000);
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
    if (counter == 0)
    {
        set_color(1, C_R);
        set_color(2, C_B);
    }
    else if (counter == 1)
    {
        set_color(1, C_G);
        set_color(2, C_G);
    }
    else if (counter == 2)
    {
        set_color(1, C_B);
        set_color(2, C_R);
    }
    else if (counter == 3)
    {
        set_color(1, C_OFF);
        set_color(2, C_OFF);
    }

	if (counter == 3) // if finished with row
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

	//if((GPIOC->ODR & 1 << LED_CLK) == 1 << LED_CLK) GPIOC->ODR ^= 1 << LED_B1;
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

void set_color(int channel, int color)
{
	/* COLOR LIST
	 * 0 -> RED
	 * 1 -> BLUE
	 * 2 -> GREEN
	 * 3 -> RED/BLUE
	 * 4 -> RED/GREEN
	 * 5 -> BLUE/GREEN
	 * 6 -> RED/BLUE/GREEN
	 * -1 (or any other int really) -> OFF
	 *
	 * CHANNEL
	 * 1 for R1, B1, G1
	 * 2 for R2, B2, G2
	*/

    if (channel == 1)
    {
        switch (color)
        {
            case 0: set_bit_c(LED_R1, 1);
                    set_bit_c(LED_B1, 0);
                    set_bit_c(LED_G1, 0);
                    break;
            case 1: set_bit_c(LED_R1, 0);
                    set_bit_c(LED_B1, 1);
                    set_bit_c(LED_G1, 0);
                    break;
            case 2: set_bit_c(LED_R1, 0);
                    set_bit_c(LED_B1, 0);
                    set_bit_c(LED_G1, 1);
                    break;
            case 3: set_bit_c(LED_R1, 1);
                    set_bit_c(LED_B1, 1);
                    set_bit_c(LED_G1, 0);
                    break;
            case 4: set_bit_c(LED_R1, 1);
                    set_bit_c(LED_B1, 0);
                    set_bit_c(LED_G1, 1);
                    break;
            case 5: set_bit_c(LED_R1, 0);
                    set_bit_c(LED_B1, 1);
                    set_bit_c(LED_G1, 1);
                    break;
            case 6: set_bit_c(LED_R1, 1);
                    set_bit_c(LED_B1, 1);
                    set_bit_c(LED_G1, 1);
                    break;
            default: set_bit_c(LED_R1, 0);
                     set_bit_c(LED_B1, 0);
                     set_bit_c(LED_G1, 0);
                     break;
        }
    }
    else if (channel == 2)
    {
        switch (color)
        {
            case 0: set_bit_c(LED_R2, 1);
                    set_bit_c(LED_B2, 0);
                    set_bit_c(LED_G2, 0);
                    break;
            case 1: set_bit_c(LED_R2, 0);
                    set_bit_c(LED_B2, 1);
                    set_bit_c(LED_G2, 0);
                    break;
            case 2: set_bit_c(LED_R2, 0);
                    set_bit_c(LED_B2, 0);
                    set_bit_c(LED_G2, 1);
                    break;
            case 3: set_bit_c(LED_R2, 1);
                    set_bit_c(LED_B2, 1);
                    set_bit_c(LED_G2, 0);
                    break;
            case 4: set_bit_c(LED_R2, 1);
                    set_bit_c(LED_B2, 0);
                    set_bit_c(LED_G2, 1);
                    break;
            case 5: set_bit_c(LED_R2, 0);
                    set_bit_c(LED_B2, 1);
                    set_bit_c(LED_G2, 1);
                    break;
            case 6: set_bit_c(LED_R2, 1);
                    set_bit_c(LED_B2, 1);
                    set_bit_c(LED_G2, 1);
                    break;
            default: set_bit_c(LED_R2, 0);
                     set_bit_c(LED_B2, 0);
                     set_bit_c(LED_G2, 0);
                     break;
        }
    }
    else
    {
        for(;;);
    }
}
