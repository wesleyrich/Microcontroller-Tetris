/*
 * leaderboard.c
 *
 *  Created on: Nov 23, 2019
 *      Author: rich27
 */

#include "leaderboard.h"
#include "led_matrix.h"
#include "constants.h"
#include "state_manager.h"
#include "eeprom.h"

int range = 0;
uint8_t ** letters_arr [] = {*letter_a, *letter_b, *letter_c, *letter_d, *letter_e, *letter_f, *letter_g, *letter_h, *letter_i, *letter_j, *letter_k, *letter_l,
		*letter_m, *letter_n, *letter_o, *letter_p, *letter_q, *letter_r, *letter_s, *letter_t, *letter_u, *letter_v, *letter_w, *letter_x, *letter_y,
		*letter_z, *letter_exclamation, *letter_question};

void initialize_leaderboard()
{
	draw_rect(0,0,31,63,-1);
	draw_rect(1,56,30,56,5);

	draw_rect(1,58,1,62,4);
	draw(2,60,4);
	draw_rect(3,58,3,62,4);
	draw_rect(5,58,5,62,4);

	draw_rect(8,62,10,62,6);
	draw_rect(8,60,8,61,6);
	draw_rect(9,60,10,60,6);
	draw_rect(10,58,10,59,6);
	draw_rect(8,58,9,58,6);

	draw_rect(12,62,14,62,6);
	draw_rect(12,58,12,61,6);
	draw_rect(13,58,14,58,6);

	draw_rect(16,62,18,62,6);
	draw_rect(16,58,16,61,6);
	draw_rect(17,58,18,58,6);
	draw_rect(18,59,18,61,6);

	draw_rect(20,62,22,62,6);
	draw_rect(20,58,20,61,6);
	draw_rect(22,60,22,61,6);
	draw(21,59,6);
	draw(22,58,6);

	draw_rect(24,62,26,62,6);
	draw_rect(24,58,24,62,6);
	draw_rect(25,58,26,58,6);
	draw(25,60,6);

	draw_rect(28,62,30,62,6);
	draw_rect(28,60,28,61,6);
	draw_rect(28,60,29,60,6);
	draw_rect(30,58,30,60,6);
	draw_rect(28,58,29,58,6);

	draw_range();
}

void draw_range()
{
	for (int i = 0; i < 4; i++)
	{
		draw_score(get_highscores(i + range*4), 27, 47 - (i * 14), 4);
		draw_rank(range * 4 + i+1,7,53 - (i * 14),6);
		draw(13,52 - (i *14),6);
		draw(13,50 - (i *14),6);
		uint32_t letters = get_name(i + range*4);
		uint8_t l1 = (letters & 0xff) % 28;
		uint8_t l2 = ((letters >> 8) & 0xff) % 28;
		uint8_t l3 = ((letters >> 16) & 0xff) % 28;
		draw_letter((letters_arr[l1]), 17, 53 - 14 * i, 5);
		draw_letter((letters_arr[l2]), 22, 53 - 14 * i, 5);
		draw_letter((letters_arr[l3]), 27, 53 - 14 * i, 5);
	}
}

void draw_letter(uint8_t letter[5][4], int x, int y, int color)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if(letter[i][j] == 1)
			{
				draw(j + x, -i + y, color);
			}
		}
	}
}



void handle_input_leaderboard()
{
	if (getState() != 2)
	    {
	        return;
	    }

	    if (get_buttons(but_SEL))
	    {
	    	setState(0);
	    }
	    if (get_buttons(but_UP) && range > 0)
	    {
	    	range--;
	    	initialize_leaderboard();
	    }
	    if (get_buttons(but_DOWN) && range < 4)
	    {
	    	range++;
	    	initialize_leaderboard();
	    }
}
