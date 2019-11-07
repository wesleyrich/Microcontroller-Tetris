/*
 * led_matrix.c
 *
 *  Created on: Oct 30, 2019
 *      Author: Grant, Wesley, Daryl
 */



#include "stm32f0xx.h"
#include "stm32f0_discovery.h"
#include "pieces.h"


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

int toggle_bit_c(int code);
void set_bit_c(int code, int state);
void set_row(int row);
void update_led();
void set_color(uint8_t channel, uint8_t color);
void nano_wait(unsigned int n);
void draw(int x, int y, int color);
void draw_rect(int x1, int y1, int x2, int y2, uint8_t color);
void draw_piece(const uint8_t shape [4][4], int x, int y, int color);


uint8_t pixels [32][64]; // x are the columns, y are the rows

// TETROMINOS

//top left pixel is start goes from top row to bottom row, 0 2x2 is on right

//I
const uint8_t I0[4][4] = {{1,1,1,1}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}}; //0 rotations I
const uint8_t I1[4][4] = {{1,0,0,0}, {1,0,0,0}, {1,0,0,0}, {1,0,0,0}}; //1 rotations I
const uint8_t I2[4][4] = {{1,1,1,1}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}}; //2 rotations I
const uint8_t I3[4][4] = {{1,0,0,0}, {1,0,0,0}, {1,0,0,0}, {1,0,0,0}}; //3 rotations I

//T
const uint8_t T0[4][4] = {{1,1,1,0}, {0,1,0,0}, {0,0,0,0}, {0,0,0,0}}; //0 rotation T
const uint8_t T1[4][4] = {{0,1,0,0}, {1,1,0,0}, {0,1,0,0}, {0,0,0,0}}; //1 rotation T
const uint8_t T2[4][4] = {{0,1,0,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0}}; //2 rotations T
const uint8_t T3[4][4] = {{1,0,0,0}, {1,1,0,0}, {1,0,0,0}, {0,0,0,0}}; //3 rotations T

//0
const uint8_t O0[4][4] = {{1,1,0,0}, {1,1,0,0}, {0,0,0,0}, {0,0,0,0}}; //0 rotations O
const uint8_t O1[4][4] = {{1,1,0,0}, {1,1,0,0}, {0,0,0,0}, {0,0,0,0}}; //1 rotations O
const uint8_t O2[4][4] = {{1,1,0,0}, {1,1,0,0}, {0,0,0,0}, {0,0,0,0}}; //2 rotations O
const uint8_t O3[4][4] = {{1,1,0,0}, {1,1,0,0}, {0,0,0,0}, {0,0,0,0}}; //3 rotations O

//l
const uint8_t L0[4][4] = {{1,1,1,0}, {1,0,0,0}, {0,0,0,0}, {0,0,0,0}}; //0 rotations l
const uint8_t L1[4][4] = {{1,1,0,0}, {0,1,0,0}, {0,1,0,0}, {0,1,0,0}}; //1 rotations l
const uint8_t L2[4][4] = {{0,0,1,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0}}; //2 rotations l
const uint8_t L3[4][4] = {{1,0,0,0}, {1,0,0,0}, {1,1,0,0}, {0,0,0,0}}; //3 rotations l

//j
const uint8_t J0[4][4] = {{1,1,1,0}, {0,0,1,0}, {0,0,0,0}, {0,0,0,0}}; //0 rotations j
const uint8_t J1[4][4] = {{0,1,0,0}, {0,1,0,0}, {1,1,0,0}, {0,0,0,0}}; //1 rotations j
const uint8_t J2[4][4] = {{1,0,0,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0}}; //2 rotations j
const uint8_t J3[4][4] = {{1,1,0,0}, {1,0,0,0}, {1,0,0,0}, {0,0,0,0}}; //3 rotations j

//z
const uint8_t Z0[4][4] = {{1,1,0,0}, {0,1,1,0}, {0,0,0,0}, {0,0,0,0}}; //0 rotations z
const uint8_t Z1[4][4] = {{0,1,0,0}, {1,1,0,0}, {1,0,0,0}, {0,0,0,0}}; //1 rotations z
const uint8_t Z2[4][4] = {{1,1,0,0}, {0,1,1,0}, {0,0,0,0}, {0,0,0,0}}; //2 rotations z
const uint8_t Z3[4][4] = {{0,1,0,0}, {1,1,0,0}, {1,0,0,0}, {0,0,0,0}}; //3 rotations z

//z
const uint8_t S0[4][4] = {{0,1,1,0}, {1,1,0,0}, {0,0,0,0}, {0,0,0,0}}; //0 rotations s
const uint8_t S1[4][4] = {{1,0,0,0}, {1,1,0,0}, {0,0,1,0}, {0,0,0,0}}; //1 rotations s
const uint8_t S2[4][4] = {{0,1,1,0}, {1,1,0,0}, {0,0,0,0}, {0,0,0,0}}; //2 rotations s
const uint8_t S3[4][4] = {{1,0,0,0}, {1,1,0,0}, {0,1,0,0}, {0,0,0,0}}; //3 rotations s


void nano_wait(unsigned int n) {
    asm(    "        mov r0,%0\n"
            "repeat: sub r0,#83\n"
            "        bgt repeat\n" : : "r"(n) : "r0", "cc");
}

void draw(int x, int y, int color)
{
	pixels[x][y] = color;
}

void initialize_pixels()
{
	for (int i = 0; i < 32; i++)
	{
		for (int j = 0; j < 64; j++)
		{
			pixels[i][j] = -1;
		}
	}
//	for (int i = 0; i < 32; i++)
//	{
//		for (int j = 0; j < 4; j++)
//		{
//			pixels[i + 4 * j + 20][i] = i % 7;
//		}
//	}
	for (int i = 0; i < 64; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			draw(j,i,-1);
		}
	}

	// draw the border
	draw_rect(0,14,22,55,6);
	draw_rect(1,15,21,54,7);
	// draw tetris
	// T
	draw_rect(2,62,6,62,0);
	draw_rect(4,58,4,61,0);
	// E
	draw_rect(9,62,11,62,4);
	draw_rect(9,60,10,60,4);
	draw_rect(9,58,11,58,4);
	draw_rect(8,58,8,62,4);
	// T
	draw_rect(13,62,17,62,2);
	draw_rect(15,58,15,61,2);
	// R
	draw_rect(19,62,22,62,5);
	draw_rect(19,58,19,61,5);
	draw(22,61,5);
	draw_rect(19,60,22,60,5);
	draw(21,59,5);
	draw(22,58,5);
	// I
	draw_rect(24,58,24,62,1);
	// S
	draw_rect(26,62,29,62,3);
	draw_rect(26,60,26,61,3);
	draw_rect(27,60,29,60,3);
	draw_rect(29,58,29,59,3);
	draw_rect(26,58,28,58,3);

//	switch(pieceNum)
//	{
//		case 0:
//			draw_piece(I0,1,54,1);
//			break;
//		case 1:
//			draw_piece(I1,1,54,1);
//			break;
//		case 2:
//			draw_piece(I2,1,54,1);
//			break;
//		case 3:
//			draw_piece(I3,1,54,1);
//			break;
//		case 4:
//			draw_piece(Z0,1,54,1);
//			break;
//		case 5:
//			draw_piece(Z1,1,54,1);
//			break;
//		case 6:
//			draw_piece(Z2,1,54,1);
//			break;
//		case 7:
//			draw_piece(Z3,1,54,1);
//			break;
//		case 8:
//			draw_piece(T0,1,54,1);
//			break;
//		case 9:
//			draw_piece(T1,1,54,1);
//			break;
//		case 10:
//			draw_piece(T2,1,54,1);
//			break;
//		case 11:
//			draw_piece(T3,1,54,1);
//			break;
//		case 12:
//			draw_piece(L0,1,54,1);
//			break;
//		case 13:
//			draw_piece(L1,1,54,1);
//			break;
//		case 14:
//			draw_piece(L2,1,54,1);
//			break;
//		case 15:
//			draw_piece(L3,1,54,1);
//			break;
//		case 16:
//			draw_piece(J0,1,54,1);
//			break;
//		case 17:
//			draw_piece(J1,1,54,1);
//			break;
//		case 18:
//			draw_piece(J2,1,54,1);
//			break;
//		case 19:
//			draw_piece(J3,1,54,1);
//			break;
//		case 20:
//			draw_piece(O0,1,54,1);
//			break;
//		case 21:
//			draw_piece(O1,1,54,1);
//			break;
//		case 22:
//			draw_piece(O2,1,54,1);
//			break;
//		case 23:
//			draw_piece(O3,1,54,1);
//			break;
//		case 24:
//			draw_piece(S0,1,54,1);
//			break;
//		case 25:
//			draw_piece(S1,1,54,1);
//			break;
//		case 26:
//			draw_piece(S2,1,54,1);
//			break;
//		case 27:
//			draw_piece(S3,1,54,1);
//	}
}

void LED_pins_setup ()
{
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN; 	// enable clock to GPIOA
	// set pins 0-12 for output
	GPIOC->MODER &= ~(0x3ffffff);
	GPIOC->MODER |= (0x1555555);
	set_bit_c(LED_OE, 0);
	set_bit_c(LED_LAT, 0);
	set_row(0);
}

int led_counter = 0;

void update_led() // reading one bit too many
{

	if (!toggle_bit_c(LED_CLK)) // if its on a high clock cycle update the leds
	{
		return;
	}

	if (led_counter >= (64 * 32 / 2)) // check if cycle is complete
	{
		led_counter = 0;
		return;
	}

	int x, y;

	x = led_counter / 64; // the column
	y = led_counter % 64; // the row

	uint8_t color_top = pixels[x][y];
	uint8_t color_bot = pixels[x+16][y];

	set_color(1, color_top);
	set_color(2, color_bot);

	if (y == 63) // we've finished this row, latch and enable.
	{
		set_bit_c(LED_LAT, 1);
		set_bit_c(LED_OE, 1);

		toggle_bit_c(LED_CLK); // toggle clock

		set_row(x);

		toggle_bit_c(LED_CLK); // toggle clock

		set_bit_c(LED_OE, 0);
		set_bit_c(LED_LAT, 0);
	}

	led_counter++;

}

int toggle_bit_c(int code) // toggles a bit and returns the new state
{
	GPIOC->ODR ^= 1 << code; // toggle bit
	return ((GPIOC->ODR & 1 << code) >> code); // return the new state
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

void draw_rect(int x1, int y1, int x2, int y2, uint8_t color) // x is column, y is row
{
	for (int i = x1; i <= x2; i++)
	{
		for (int j = y1; j <= y2; j++)
		{
			draw(i, j, color);
		}
	}
}

void draw_piece(const uint8_t shape[4][4], int x, int y, int color)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{

			if(shape[i][j] == 1)
			{
				draw(2*j + x, -2*i + y, color);
				draw(2*j + x + 1, -2*i + y, color);
				draw(2*j + x, -2*i + y - 1, color);
				draw(2*j + x + 1, -2*i + y - 1, color);

			}
		}
	}
}

void set_color(uint8_t channel, uint8_t color)
{
	/* COLOR LIST
	 * 0 -> RED
	 * 1 -> BLUE
	 * 2 -> GREEN
	 * 3 -> RED/BLUE (Magenta)
	 * 4 -> RED/GREEN (Yellow)
	 * 5 -> BLUE/GREEN (Cyan)
	 * 6 -> RED/BLUE/GREEN (White)
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
