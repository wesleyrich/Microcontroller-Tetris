/*
 * led_matrix.c
 *
 *  Created on: Oct 31, 2019
 *      Author: Wesley
 */

#include "stm32f0xx.h"
#include "stm32f0_discovery.h"

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
 *      10–12   5
 *      13–15   4
 *      16–18   3
 *      19–28   2
 *      29+     1
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
 *   I'm going to implement a Fibonacci linear feedback shift register to
 *   imitate randomness of pieces just like the NES did. This will need to be
 *   called constantly to perpetuate the PRNG, including on the title screen
 *   before the game begins. The order that the pieces appear in are randomized,
 *   as well as their starting orientation. The only stipulation is that you
 *   cannot get the same piece twice in a row. If this happens, the LFSR must
 *   be called again until a different piece is retrieved
 *
 * Tetromino Rotation:
 *
 * Collision Testing:
 *
 * Clearing Lines:
 *
 * Scoring:
 *
 */

#define TIM2_FREQ 12000000 // must be the same as in main.c

int LFSR(int init);
int get_piece();
void update_tetris();
void initialize_game();

const uint8_t framerate_by_level [] = {48, 43, 38, 33, 28, 23, 18, 13, 8, 6, 5, 4, 3, 2, 1};
uint8_t level = 0;

void initialize_game () // stuff to do at startup
{

}


int count_to = (TIM2_FREQ / 48);
int game_counter = 0;

void update_tetris () // game goes in here
{
	if (game_counter < count_to)
	{
		game_counter++;
		return;
	}
}


int rng = 0; //feedback variable for the LSFR
int get_piece()
{
    /* PIECES LIST
     * (Each piece will be represented by 4 values, 1 for each orientation)
     *
     * T -> 0: 00000  1: 00000  2: 00000  3: 00000
     *         00100     00100     00000     00100
     *         01110     00110     01110     01100
     *         00000     00100     00100     00100
     *         00000     00000     00000     00000
     *
     * J -> 4: 00000  5: 00000  6: 00000  7: 00000
     *         00100     01000     00110     00000
     *         00100     01110     00100     01110
     *         01100     00000     00100     00010
     *         00000     00000     00000     00000
     *
     * Z -> 8: 00000  9: 00000 10: xxxxx 11: xxxxx
     *         00000     00010     xxxxx     xxxxx
     *         01100     00110     xxxxx     xxxxx
     *         00110     00100     xxxxx     xxxxx
     *         00000     00000     xxxxx     xxxxx
     *
     * O ->12: 00000 13: xxxxx 14: xxxxx 15: xxxxx
     *         00000     xxxxx     xxxxx     xxxxx
     *         01100     xxxxx     xxxxx     xxxxx
     *         01100     xxxxx     xxxxx     xxxxx
     *         00000     xxxxx     xxxxx     xxxxx
     *
     * S ->16: 00000 17: 00000 18: xxxxx 19: xxxxx
     *         00000     00100     xxxxx     xxxxx
     *         00110     00110     xxxxx     xxxxx
     *         01100     00010     xxxxx     xxxxx
     *         00000     00000     xxxxx     xxxxx
     *
     * L ->20: 00000 21: 00000 22: 00000 23: 00000
     *         00100     00000     01100     00010
     *         00100     01110     00100     01110
     *         00110     01000     00100     00000
     *         00000     00000     00000     00000
     *
     * I ->24: 00100 25: 00000 26: xxxxx 27: xxxxx
     *         00100     00000     xxxxx     xxxxx
     *         00100     00000     xxxxx     xxxxx
     *         00100     11110     xxxxx     xxxxx
     *         00000     00000     xxxxx     xxxxx
     */
    uint8_t piece_mask = 0b111;
    uint8_t orient_mask = 0b11000;
    uint8_t piece = 0; //representing our tetromino
    uint8_t prev_piece = 7;
    uint8_t orient = 0;

    //THIS WILL NEED TO BE IN MAIN (below two lines)
    int seed = 0b1001011010100111;
    rng = LFSR(seed);

    rng = LFSR(rng);
    piece = piece_mask & rng;
    while(piece == prev_piece || piece == 7)
    {
        rng = LFSR(rng);
        piece = piece_mask & rng;
    }
    prev_piece = piece;

    orient = orient_mask & rng;
    orient = orient >> 3;

    // transforming into one of the above codes
    piece *= 4;
    piece += orient;

    // removing non-existent orientations
    // **note that this does make certain orientations slightly more likely than
    // others but I'm too tired to care right now**
    if(piece == 15) piece--;
    if(piece == 11 || piece == 14 || piece == 19 || piece == 27) piece--;
    if(piece == 10 || piece == 13 || piece == 18 || piece == 26) piece--;

    return(piece);
}

int LFSR(int init)
{
    return ((((init >> 9) & 1) ^ ((init >> 1) & 1)) << 15) | (init >> 1);
}
