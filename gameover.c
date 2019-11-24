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

uint8_t ** letters_arr2 [] = {*letter_a, *letter_b, *letter_c, *letter_d, *letter_e, *letter_f, *letter_g, *letter_h, *letter_i, *letter_j, *letter_k, *letter_l,
        *letter_m, *letter_n, *letter_o, *letter_p, *letter_q, *letter_r, *letter_s, *letter_t, *letter_u, *letter_v, *letter_w, *letter_x, *letter_y,
        *letter_z, *letter_exclamation, *letter_question};

int let_selected = 0;

void initialize_gameover()
{
    if (getScore() < get_highscores(19))

    {
        // youre a loser
        setState(2);
        return;
    }


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

    let_selected = 0;
    let_arr[0] = 0;
    let_arr[1] = 0;
    let_arr[2] = 0;
    draw_rect(1,46,9,46,4);
    draw_rect(21,46,30,46,4);
    draw_rank(1,16,48,6);
    draw_score(getScore(), 27, 40, 4);
    draw_let_arr(5);
    draw_selected(6);

}



void handle_input_gameover()
{
    if (getState() != 5) {
        return;
    }

    if (get_buttons(but_START))
    {
        //setState(1);
        return;
    }
    if (get_buttons(but_SEL))
    {
        //setState(0);
        return;
    }

    if (get_buttons(but_LEFT) && let_selected > 0)
    {
        draw_selected(7);
        let_selected--;
        draw_selected(6);
    }
    if (get_buttons(but_RIGHT) && let_selected < 2)
    {
        draw_selected(7);
        let_selected++;
        draw_selected(6);
    }

    if (get_buttons(but_UP))
    {
        draw_let_arr(7);
        let_arr[let_selected]++;
        if (let_arr[let_selected] > 28)
        {
            let_arr[let_selected] = 0;
        }
        draw_let_arr(5);
    }

    if (get_buttons(but_DOWN))
      {
        draw_let_arr(7);
          let_arr[let_selected]--;
          if (let_arr[let_selected] > 28)
          {
              let_arr[let_selected] = 27;
          }
        draw_let_arr(5);
      }
    if (get_buttons(but_A))
    {
        // save highscore and name into the position of the current lowest score

        int addr = get_address(get_highscores(19));
        uint32_t name = let_arr[0] + (let_arr[1] << 8) + (let_arr[2] << 16);
        write_EEPROM(addr, name);
        write_EEPROM(addr + 4, getScore());
        read_and_sort();
        setState(2);
        return;
    }
}

void draw_selected(int color)
{
    draw_rect(9 + let_selected * 5,22, 12 + let_selected * 5, 22,color);
}

void draw_let_arr (int color)
{
    draw_letter(letters_arr2[let_arr[0]], 9, 28, color);
    draw_letter(letters_arr2[let_arr[1]], 14, 28, color);
    draw_letter(letters_arr2[let_arr[2]], 19, 28, color);
}
