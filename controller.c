/*
 * controller.c
 *
 *  Created on: Nov 11, 2019
 *      Author: rich27
 */

#include "stm32f0xx.h"
#include "stm32f0_discovery.h"
#include "constants.h"
#include "led_matrix.h"
#include "tetris.h"
#include "pieces.h"
#include "controller.h"


void initialize_controller()
{
	/* pa0 is clk
	 * pa1 is latch
	 * pa2 is data */

	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	GPIOA->MODER &= ~(GPIO_MODER_MODER0 | GPIO_MODER_MODER1 | GPIO_MODER_MODER2);
	GPIOA->MODER |= (GPIO_MODER_MODER0_0 | GPIO_MODER_MODER1_0);
}

// Sets a bit in GPIOA based on state. State must be 0 or 1
void set_bit_a(uint8_t code, uint8_t state)
{
	if(state == 1)
	{
		GPIOA->BSRR = 1 << code;
	}
	else if(state == 0)
	{
		GPIOA->BSRR = 1 << (code + 16);
	}
	else //infinitely looping
	{
		for(;;);
	}
}

uint8_t toggle_bit_a(uint8_t code) // toggles a bit and returns the new state
{
	GPIOA->ODR ^= 1 << code; // toggle bit
	return ((GPIOA->ODR & 1 << code) >> code); // return the new state
}

int update_every = 100;
int counter = 0;
int controller_counter = 0;
volatile uint8_t hold_data = 0;
volatile uint8_t last_data = 0;
volatile uint8_t c_data = 0;
volatile uint8_t buttons_held = 0;

void update_controller()
{
	if (counter < update_every)
	{
		counter++;
		return;
	}
	counter = 0;
	if (controller_counter == 0)
	{
		set_bit_a(CTRL_LAT, 1);
		controller_counter++;
		return;
	}

	else if (controller_counter == 1)
	{
		set_bit_a(CTRL_LAT, 0);
		c_data <<= 1;
		c_data += (GPIOA->IDR & (1 << CTRL_DAT)) >> CTRL_DAT;
		controller_counter++;
	}

	else if (controller_counter > 1)
	{
		if (toggle_bit_a(CTRL_CLK))
			{
				return;
			}
		set_bit_a(CTRL_LAT, 0);
		c_data <<= 1;
		c_data += (GPIOA->IDR & (1 << CTRL_DAT)) >> CTRL_DAT;
		controller_counter++;
	}

	if (controller_counter > 8)
	{
		toggle_bit_a(CTRL_CLK);
		toggle_bit_a(CTRL_CLK);
		hold_data |= ~c_data; // or equal to the data aquired over the last cycle
		buttons_held = hold_data;
		hold_data &= ~last_data; // remove any bits that were triggered previously
		last_data &= ~c_data;
		c_data = 0;
		controller_counter = 0;
		if (hold_data != 0)
		{
			handle_input();
		}
	}
}

uint8_t get_buttons(uint8_t button)
{
	return (hold_data & 1 << button) >> button;
}

uint8_t get_buttons_held(uint8_t button)
{
    return (buttons_held & 1 << button) >> button;
}

void clear_buttons()
{
	last_data |= hold_data;
	buttons_held = 0;
	hold_data = 0;
}
