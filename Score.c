#include "stm32f0xx.h"
#include "stm32f0_discovery.h"
#include "constants.h"
#include "led_matrix.h"
#include "tetris.h"
#include "pieces.h"

//points for 1 line = 40 * (n + 1) where n is the level number
//points for 2 line = 100 * (n + 1) where n is the level number
//points for 3 line = 300 * (n + 1) where n is the level number
//points for 4 line = 1200 * (n + 1) where n is the level number

void initialize_symbols ()
{
    draw(3,12,6);
    draw_rect(2,11,4,11,6);
    draw_rect(1,10,5,10,6);
    draw_rect(3,8,3,9,6);

    draw(3,6,4);
    draw_rect(1,5,5,5,4);
    draw_rect(2,4,4,4,4);
    draw_rect(2,3,4,3,4);
    draw_rect(1,2,2,2,4);
    draw_rect(4,2,5,2,4);

    draw_rect(7,12,10,12,6);
    draw_rect(7,8,7,11,6);
    draw_rect(8,8,10,8,6);
    draw_rect(10,8,10,11,6);
}

void initialize_numbers ()
{
    draw_rect(7,12,10,12,6);
    draw_rect(7,8,7,11,6);
    draw_rect(8,8,10,8,6);
    draw_rect(8,8,8,10,6);
}


void draw_number(const uint8_t shape[4][5], int x, int y, int color)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 5; j++)
        {

            if(shape[i][j] == 1)
            {
                draw(j + x, -2*i + y, color);
                draw(j + x + 1, -2*i + y, color);
                draw(j + x, -2*i + y - 1, color);
                draw(j + x + 1, -2*i + y - 1, color);

            }
        }
    }
}

