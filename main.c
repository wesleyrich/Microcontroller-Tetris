/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    11/2/19
  * @brief   Main function for Tetris Game
  ******************************************************************************
*/

// LOCKER CODE: 7932

#include "stm32f0xx.h"
#include "stm32f0_discovery.h"
#include "stdint.h"
#include "constants.h"
#include "led_matrix.h"
#include "tetris.h"
#include "pieces.h"
#include "Score.h"
#include "controller.h"
#include "menu.h"
#include "state_manager.h"
#include "eeprom.h"
#include "audio.h"
#include "leaderboard.h"

//#include "pieces.h"


void tim2_setup();

float temp_rng = 123;

int main(void)
{

    initialize_eeprom();
    read_and_sort();
/*
    for (int i = 0; i < 80; i++)
    {
        write_EEPROM(i*4, 0);
        write_EEPROM((i+1)*4,0);
    }

    read_and_sort();
*/
	LED_pins_setup();
	initialize_controller();
    test_audio();
	initialize_menu();
	tim2_setup();




	for(;;)
	{
	    update_led();
	}
}

void tim2_setup ()
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; // enable clock to tim6

	// set up the clock frequency
	TIM2->ARR = 1;
	TIM2->PSC = (int)(48000000 / TIM2_FREQ / 2) - 1; //assuming ARR is '1'

	TIM2->DIER |= TIM_DIER_UIE; 		// enable the update interrupt
	TIM2->CR1 |= TIM_CR1_CEN; 			// enable the timer counter
	NVIC->ISER[0] = 1 << TIM2_IRQn;     // enable the interrupt
}

void TIM2_IRQHandler ()
{

    TIM2->SR &= ~TIM_SR_UIF; // acknowledge the interrupt

	update_controller(); // this function is going to update the controller, hence the name (*cause Grant is being weird about things like this*)

	switch (getState())
	{
	case 0:
	    //update_menu();
	    break;
	case 1:
	    update_tetris();
	    break;
	case 2:
		//update_leaderboard();
		break;
	}
}



