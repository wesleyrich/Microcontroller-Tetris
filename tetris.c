/*
 * led_matrix.c
 *
 *  Created on: Oct 31, 2019
 *      Author: Wesley
 */

#include "stm32f0xx.h"
#include "stm32f0_discovery.h"
#include "constants.h"
#include "led_matrix.h"
#include "tetris.h"
#include "pieces.h"
#include "controller.h"


/*
 * GENERAL NOTES
 *
 * References:
 *   https://meatfighter.com/nintendotetrisai/#The_Mechanics_of_Nintendo_Tetris
 *   https://remysharp.com/2019/09/10/blocks-of-tetris-code
 *   https://harddrop.com/wiki/Tetris_(NES,_Nintendo)
 *
 * Rules:
 *   Will be following all the rules for Tetris on the NES, except that we will
 *   attempt to implement a hard-drop feature. I've listed some notable NES
 *   Tetris rules below:
 *   - Only one next piece will be displayed by the board
 *   - No "hold piece" mechanism will be implemented
 *   - Will use the right-handed Nintendo Rotation System for tetrominos
 *   - Lock delay (waiting after a piece makes collision before "locking" it in
 *     place) and wall kick (moving a piece out from the wall to allow an
 *     otherwise impossible rotation) will not be used
 *   - Will *try* to effectively implement DAS, though I think this could
 *     be fine without it
 *   - Will implement ARE (period of time between the lockdown of one tetromino
 *     and the appearance of the next)
 *   - Gravity increases by level. Will try to adhere as close as possible to
 *     the values in this table from NES Tetris:
 *
 *     Level    Frames per Gridcell
 *      00      48
 *      01      43
 *      02      38
 *      03      33
 *      04      28
 *      05      23
 *      06      18
 *      07      13
 *      08      8
 *      09      6
 *      10-12   5
 *      13-15   4
 *      16-18   3
 *      19-28   2
 *      29+
 *
 *   - Will increase level by 1 for every 10 line clears
 *
 * Framerate:
 *   NES Tetris runs at 60 frames per second which I believe is doable on our
 *   microcontroller since we have a 48 Mhz clock (?). Maybe this is a question
 *   for Rick
 *
 * The Board:
 *   10x20 matrix will be used to represent the board. This can be done with
 *   arrays in C (int matrix[10][20]). Presence or absence of a block will be
 *   represented by a 0 or 1 at that spot in memory.
 *
 * RNG:
 *   I'm going to imple if(get_buttons(but_LEFT) && !check_collision_xneg(piece.shape)) piece.x -= 2;ment a Fibonacci linear feedback shift register to
 *   imitate randomness of pieces just like the NES did. This will need to be
 *   called constantly to perpetuate the PRNG, including on the title screen
 *   before the game begins. The order that the pieces appear in are randomized,
 *   as well as their starting orientation. The only stipulation is that you
 *   cannot get the same piece twice in a row. If this happens, the LFSR must
 *   be called again until a different piece is retrieved
 *
 * Tetromino Rotation:
 *
 * Collision Testing:int LFSR(int init);
int get_piece();
void update_tetris();
void initialize_game();
 *000
 * Clearing Lines:
 *
 * Scoring:
 *
 */

#define LAG_FACTOR 0.27   // reduce frames to count to by this factor (ie LAG_FACTOR = 0.1 reduces frames to count by 10%)

// Holds all the shapes
uint8_t * shapes[28];




const uint8_t gravity [] = {48, 43, 38, 33, 28, 23, 18, 13, 8, 6, 5, 5, 5, 4, 4, 4, 3, 3, 3, 2,2,2,2,2,2,2,2,2,2, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
uint8_t * piece_dictionary [28];
uint8_t level = 0;
uint8_t lines_cleared = 0;
struct Piece piece;
struct Piece next_piece [3];
uint8_t prev_piece = 0;
int rng = 12323; //feedback variable for the LSFR
int game_active = 0;
int ending = 0;

void initialize_game () // stuff to do at startup
{
	initialize_pixels();
	initialize_symbols();
	addScore(-getScore());
	draw_score();
	level = 0;
	lines_cleared = 0;
	draw_level(level);
    piece_dictionary[0] = *I0;
    piece_dictionary[1] = *I1;
    piece_dictionary[2] = *I2;
    piece_dictionary[3] = *I3;
    piece_dictionary[4] = *T0;
    piece_dictionary[5] = *T1;
    piece_dictionary[6] = *T2;
    piece_dictionary[7] = *T3;
    piece_dictionary[8] = *O0;
    piece_dictionary[9] = *O1;
    piece_dictionary[10] = *O2;
    piece_dictionary[11] = *O3;
    piece_dictionary[12] = *L0;
    piece_dictionary[13] = *L1;
    piece_dictionary[14] = *L2;
    piece_dictionary[15] = *L3;
    piece_dictionary[16] = *J0;
    piece_dictionary[17] = *J1;
    piece_dictionary[18] = *J2;
    piece_dictionary[19] = *J3;
    piece_dictionary[20] = *Z0;
    piece_dictionary[21] = *Z1;
    piece_dictionary[22] = *Z2;
    piece_dictionary[23] = *Z3;
    piece_dictionary[24] = *S0;
    piece_dictionary[25] = *S1;
    piece_dictionary[26] = *S2;
    piece_dictionary[27] = *S3;
    rng = LFSR(rng);
    for (int i = 0; i < 3; i++)
    {
    	int num = get_piece();
    	next_piece[i].type = num;
        next_piece[i].color = (int)(num / 4);
        next_piece[i].shape = (piece_dictionary[num]);
    	next_piece[i].x = 23;
    	next_piece[i].y = 43 - i * 10;
    	draw_piece(next_piece[i].shape, next_piece[i].x, next_piece[i].y, next_piece[i].color);
    }

    spawn_piece();
    game_active = 1;
}

int count_to = (TIM2_FREQ * (1 - LAG_FACTOR) / 120);
int count_to_2 = 4;
int game_counter = 0;
int game_counter_2 = 0;

void update_tetris () // game goes in here
{
	if (game_counter < count_to)
	{
		game_counter++;
		rng = LFSR(rng);
		return;
	}
    game_counter = 0;

	if (game_counter_2 < count_to_2)
	{
	    game_counter_2++;
	    return;
	}
	// do a frame
	if (game_active == 0)
	{
		rick();
		return;
	}
	update_piece();
	game_counter_2 = 0;
}
void handle_input ()
{
    draw_piece(piece.shape, piece.x, piece.y, -1);
    if(get_buttons(but_LEFT) && !check_collision_xneg(piece.shape))
    {
    	piece.x -= 2;
    }
    else if(get_buttons(but_RIGHT) && !check_collision_xpos(piece.shape))
    {
    	piece.x += 2;
    }
    if (get_buttons(but_B))
    {
    	rotate_piece(0);
    }
    else if (get_buttons(but_A))
    {
    	rotate_piece(1);
    }
    if (get_buttons(but_START))
    {
    	initialize_game();
    }
    if (get_buttons_held(but_DOWN))
    {
       	count_to_2 = 1;
    }
    else
    {
     	count_to_2 = gravity[level];
    }

    clear_buttons();
    draw_piece(piece.shape, piece.x, piece.y, piece.color);
}

void rotate_piece(uint8_t dir)
{
	uint8_t type = piece.type;
	if (dir == 0) // rotate left
	{
		if (type % 4 == 0)
		{
			piece.type += 3;
			piece.shape = (piece_dictionary[piece.type]);
		}
		else
		{
			piece.type -= 1;
			piece.shape = (piece_dictionary[piece.type]);
		}
	}
	if (dir == 1) // rotate right
	{
		if (type % 4 == 3)
		{
			piece.type -= 3;
			piece.shape = (piece_dictionary[piece.type]);
		}
		else
		{
			piece.type += 1;
			piece.shape = (piece_dictionary[piece.type]);
		}
	}
}

void update_piece()
{
    draw_piece(piece.shape, piece.x, piece.y, -1);
    if (check_collision_y(piece.shape))
    {
        draw_piece(piece.shape, piece.x, piece.y, piece.color);
    	check_line_clear();
        game_active = check_gameover();
        count_to_2 = gravity[level];
        spawn_piece();
        return;
    }
    piece.y -= 2;

    draw_piece(piece.shape, piece.x, piece.y, piece.color);
}

void spawn_piece()
{
	piece = next_piece[0];
	piece.x = 9; // should be 9 we changed this to make it testable
    piece.y = 54;
    for (int i = 0; i < 3; i++)
    {
    	draw_piece(next_piece[i].shape, next_piece[i].x, next_piece[i].y, 7);
    }
	for (int i = 0; i < 2; i++)
	{
		next_piece[i].shape = next_piece[i+1].shape;
		next_piece[i].color = next_piece[i+1].color;
		next_piece[i].type = next_piece[i+1].type;
	}
    int num = get_piece();
    next_piece[2].type = num;
    next_piece[2].color = (int)(num / 4);
    next_piece[2].shape = (piece_dictionary[num]);
    draw_piece(piece.shape, piece.x, piece.y, piece.color);
    for (int i = 0; i < 3; i++)
    {
    	draw_piece(next_piece[i].shape, next_piece[i].x, next_piece[i].y, next_piece[i].color);
    }
}

void update_level ()
{
    level = lines_cleared / 1;
    if (level > 30)
    {
        level = 30;
    }
    draw_level(level);
}

int check_collision_y(uint8_t shape [4][4]) // will return a 1 if there is a collision with any other pixels
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            int k = getPixels(piece.x+(2*j),piece.y-(2*i) - 2);
            if (shape[i][j] == 1 && (k < 7)) return 1;
        }
    }
    return 0;
}

int check_collision_xpos(uint8_t shape [4][4])
{
	for(int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
		{
			int k = getPixels(piece.x+(2*j) + 2, piece.y-(2*i));
			if (shape[i][j] == 1 && (k < 7)) return 1;
		}
	}
	return 0;
}

int check_collision_xneg(uint8_t shape [4][4])
{
	for(int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
		{
			int k = getPixels(piece.x+(2*j) - 1, piece.y-(2*i));
			if (shape[i][j] == 1 && (k < 7)) return 1;
		}
	}
	return 0;
}

check_line_clear()
{
	uint8_t rows [20];
	for (int y = 0; y < 40; y+=2)
	{
		rows[y / 2] = 1;
		for (int x = 0; x < 20; x+=2)
		{
			if (getPixels(x + 1,y + 15) > 6)
			{
				rows[y / 2] = 0;
				break;
			}
		}
	}
	clear_rows(rows);
}

void clear_rows(uint8_t rows[20])
{
	int lines = 0;
	int offset = 0;
	for (int y = 0; y < 40; y += 2)
	{
		if (rows[(y + offset) / 2] == 1)
		{
		    offset += 2;
			lines++;
			for (int i = 0; i < 20; i++)
			{
				for (int j = 0; j < (40 - y - 2); j++)
				{
					draw(i + 1,j + y + 15, getPixels(i + 1,j + y + 17));
				}
			}
			y -= 2;
		}
	}
	lines_cleared += lines;
	switch (lines)
	{
		case 1:
			addScore(40);
			break;
		case 2:
			addScore(100);
			break;
		case 3:
			addScore(300);
			break;
		case 4:
			addScore(1200);
			break;
		default:
			break;
	}
	draw_score();
	update_level();
}

int check_gameover()
{
	ending = rng % 2;
	for(int i=9; i<16; i++)
	{
		if(getPixels(i, 54) < 7) return 0;
	}
	return 1;
}

int get_piece()
{
    uint8_t p = rng % 28; //representing our tetromino

    while((p / 4) == prev_piece)
    {
        rng = LFSR(rng);
        p = rng % 28;
    }
    prev_piece = p / 4;

    return(p);
}

int LFSR(int init)
{
    return ((((init >> 9) & 1) ^ ((init >> 1) & 1)) << 15) | (init >> 1);
}

void rick()
{
	for(int row=15; row<55; row++)
	{
		for(int col=1; col<21; col++)
		{
			draw(col, row, getPixels(col, row+1));
		}
	}
	if(ending)
	{
	for (int col = 1; col < 21; col++)
		{
			draw(col, 54, 7);
		}
	}
}
