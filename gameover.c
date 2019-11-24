/*
 * gameover.c
 *
 *  Created on: Nov 24, 2019
 *      Author: gjulian
 */

#include "gameover.h"
#include "state_manager.h"
#include "constants.h"
#include "Score.h"
#include "led_matrix.h"
#include "leaderboard.h"

// Game-State is 5

uint8_t let_arr [3];


void initialize_gameover()
{
    draw_rect(0, 0, 31, 63, -1);
    draw_rect(1, 56, 30, 56, 5);

    draw_rect(1, 58, 1, 62, 4);
    draw(2, 60, 4);
    draw_rect(3, 58, 3, 62, 4);
    draw_rect(5, 58, 5, 62, 4);

    draw_rect(8, 62, 10, 62, 6);
    draw_rect(8, 60, 8, 61, 6);
    draw_rect(9, 60, 10, 60, 6);
    draw_rect(10, 58, 10, 59, 6);
    draw_rect(8, 58, 9, 58, 6);

    draw_rect(12, 62, 14, 62, 6);
    draw_rect(12, 58, 12, 61, 6);
    draw_rect(13, 58, 14, 58, 6);

    draw_rect(16, 62, 18, 62, 6);
    draw_rect(16, 58, 16, 61, 6);
    draw_rect(17, 58, 18, 58, 6);
    draw_rect(18, 59, 18, 61, 6);

    draw_rect(20, 62, 22, 62, 6);
    draw_rect(20, 58, 20, 61, 6);
    draw_rect(22, 60, 22, 61, 6);
    draw(21, 59, 6);
    draw(22, 58, 6);

    draw_rect(24, 62, 26, 62, 6);
    draw_rect(24, 58, 24, 62, 6);
    draw_rect(25, 58, 26, 58, 6);
    draw(25, 60, 6);

    draw_rect(28, 62, 30, 62, 6);
    draw_rect(28, 60, 28, 61, 6);
    draw_rect(28, 60, 29, 60, 6);
    draw_rect(30, 58, 30, 60, 6);
    draw_rect(28, 58, 29, 58, 6);

    let_arr[0] = 0;
    let_arr[1] = 0;
    let_arr[2] = 0;
    draw_rank(1,17,48,6);
    draw_score(getScore(), 24, 16, 4);
    draw_let_arr();
}

void handle_input_gameover()
{
    if (getState() != 5) {
        return;
    }

    if (get_buttons(but_START))
    {
        setState(1);
        return;
    }
    if (get_buttons(but_SEL))
    {
        setState(0);
        return;
    }
}

void draw_let_arr ()
{
    draw_letter(let_arr[0], 8, 40, 5);
    draw_letter(let_arr[1], 13, 40, 5);
    draw_letter(let_arr[2], 18, 40, 5);
}
