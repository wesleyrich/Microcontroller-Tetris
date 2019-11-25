/*
 * menu.c
 *
 *  Created on: Nov 13, 2019
 *      Author: gjulian
 */
#include "stm32f0xx.h"
#include "stm32f0_discovery.h"
#include "stdint.h"
#include "constants.h"
#include "audio.h"
#include "led_matrix.h"
#include "tetris.h"
#include "pieces.h"
#include "Score.h"
#include "controller.h"
#include "menu.h"
#include "state_manager.h"

void initialize_menu() {
    // clear the screen
    stop_note();
    draw_rect(0, 0, 32, 64, 7);
    // T
    draw_rect(2, 62, 6, 62, 0);
    draw_rect(4, 58, 4, 61, 0);
    // E
    draw_rect(9, 62, 11, 62, 4);
    draw_rect(9, 60, 10, 60, 4);
    draw_rect(9, 58, 11, 58, 4);
    draw_rect(8, 58, 8, 62, 4);
    // T
    draw_rect(13, 62, 17, 62, 2);
    draw_rect(15, 58, 15, 61, 2);
    // R
    draw_rect(19, 62, 22, 62, 5);
    draw_rect(19, 58, 19, 61, 5);
    draw(22, 61, 5);
    draw_rect(19, 60, 22, 60, 5);
    draw(21, 59, 5);
    draw(22, 58, 5);
    // I
    draw_rect(24, 58, 24, 62, 1);
    // S
    draw_rect(26, 62, 29, 62, 3);
    draw_rect(26, 60, 26, 61, 3);
    draw_rect(27, 60, 29, 60, 3);
    draw_rect(29, 58, 29, 59, 3);
    draw_rect(26, 58, 28, 58, 3);

    draw_play_outline(6);
    draw_leaderboard_outline(6);
    draw_music_outline(6);
    draw_difficulty_outline(6);
    draw_other_outline(6);

    draw_music();
    change_selected();

}

uint8_t selected_color = 4;
int last_selected = 0;
int selected = 0;
int music_on = 1;
int difficulty = 0;

int get_difficulty()
{
    return difficulty;
}

int get_music_state()
{
    return music_on;
}

void set_music_state(int state)
{
    music_on = state;
}

void handle_input_menu()
{
    if (getState() != 0)
    {
        return;
    }

    if (get_buttons(but_A))
    {
        switch (selected)
        {
        case 0: // PLAY GAME
            setState(1);
            break;
        case 1: // LEADERBOARDS
            setState(2);
            break;
        case 2: // MUSIC
            music_on = !music_on;
            draw_music();
            break;
        case 3: //difficulty
            if(difficulty == 2) difficulty = 0;
            else difficulty++;
            draw_difficulty();
        }
    }

    if (selected < 4 && (get_buttons(but_DOWN) || (get_buttons(but_RIGHT))))
    {
        // move down
        selected += 1;
        change_selected();
    }
    else if (selected > 0 && (get_buttons(but_UP) || (get_buttons(but_LEFT))))
    {
        // move down
        selected -= 1;
        change_selected();
    }
}

void change_selected() {
    switch (last_selected) {
    case 0:
        draw_play_outline(6);
        break;
    case 1:
        draw_leaderboard_outline(6);
        break;
    case 2:
        draw_music_outline(6);
        break;
    case 3:
        draw_difficulty_outline(6);
        break;
    case 4:
        draw_other_outline(6);
        break;
    }
    switch (selected) {
    case 0:
        draw_play_outline(selected_color);
        break;
    case 1:
        draw_leaderboard_outline(selected_color);
        break;
    case 2:
        draw_music_outline(selected_color);
        break;
    case 3:
        draw_difficulty_outline(selected_color);
        break;
    case 4:
        draw_other_outline(selected_color);
        break;
    }
    last_selected = selected;
    draw_play(1);
    draw_music();
    draw_difficulty();
    draw_leaderboard();
}

void draw_play(uint8_t color)
{
    // P
    draw_rect(3,38,4,52,color);
    draw_rect(4,47,9,52,color);
    draw_rect(5,48,8,51,7);
    // L
    draw_rect(11,47,12,52,color);
    draw_rect(12,47,15,47,color);
    // A
    draw_rect(17, 47,22,52,color);
    draw_rect(19,47,21,48,7);
    draw_rect(19,50,21,51,7);
    // Y
    draw_rect(24,47,28,52,color);
    draw_rect(26,50,27,52,7);
    draw_rect(24,48,27,48,7);
}

void draw_leaderboard ()
{
    draw_rect(15,27,18,30, 3);
    draw_rect(20,27,22,36, 4);
    draw_rect(24,27,27,33, 5);
}

void draw_music ()
{
    int color = 6;
    if (music_on)
    {
        draw_rect(4,30,8,30,color - 1);
        draw_rect(4,26,4,30,color - 1);
        draw_rect(8,26,8,30,color - 1);
        draw_rect(3,25,4,26,color - 1);
        draw_rect(7,25,8,26,color - 1);

        draw_rect(5,21,7,21,color - 2);
        draw_rect(5,17,5,21,color - 2);
        draw_rect(4,16,5,17,color - 2);

        draw_rect(13,20,17,20,color - 3);
        draw_rect(13,16,13,20,color - 3);
        draw_rect(13,18,17,18,color - 3);
        draw_rect(17,16,17,20,color - 3);
        draw_rect(12,15,13,16,color - 3);
        draw_rect(16,15,17,16,color - 3);

        draw_rect(15,13,17,13,color - 4);
        draw_rect(15,9,15,13,color - 4);
        draw_rect(14,8,15,9,color - 4);
    }
    else
    {
        draw_rect(4,30,8,30,color);
        draw_rect(4,26,4,30,color);
        draw_rect(8,26,8,30,color);
        draw_rect(3,25,4,26,color);
        draw_rect(7,25,8,26,color);

        draw_rect(5,21,7,21,color);
        draw_rect(5,17,5,21,color);
        draw_rect(4,16,5,17,color);

        draw_rect(13,20,17,20,color);
        draw_rect(13,16,13,20,color);
        draw_rect(13,18,17,18,color);
        draw_rect(17,16,17,20,color);
        draw_rect(12,15,13,16,color);
        draw_rect(16,15,17,16,color);

        draw_rect(15,13,17,13,color);
        draw_rect(15,9,15,13,color);
        draw_rect(14,8,15,9,color);
    }
}

void draw_difficulty() {
    int color = 6;

    if (difficulty == 0) {
        draw(24,20,color - 4); //face 1
        draw(27,20,color - 4);
        draw(24,18,color - 4);
        draw(25,17,color - 4);
        draw(26,17,color - 4);
        draw(27,18,color - 4);

        draw(24,12,color); //face 2
        draw(27,12,color);
        draw(24,9,color);
        draw(25,9,color);
        draw(26,9,color);
        draw(27,9,color);

        draw(24,5,color); //face 3
        draw(27,5,color);
        draw(24,2,color);
        draw(25,3,color);
        draw(26,3,color);
        draw(27,2,color);
    }
    else if (difficulty == 1) {
        draw(24,20,color); //face 1
        draw(27,20,color);
        draw(24,18,color);
        draw(25,17,color);
        draw(26,17,color);
        draw(27,18,color);

        draw(24,12,color - 2); //face 2
        draw(27,12,color - 2);
        draw(24,9,color - 2);
        draw(25,9,color - 2);
        draw(26,9,color - 2);
        draw(27,9,color - 2);

        draw(24,5,color); //face 3
        draw(27,5,color);
        draw(24,2,color);
        draw(25,3,color);
        draw(26,3,color);
        draw(27,2,color);
    }
    else {
        draw(24,20,color); //face 1
        draw(27,20,color);
        draw(24,18,color);
        draw(25,17,color);
        draw(26,17,color);
        draw(27,18,color);

        draw(24,12,color); //face 2
        draw(27,12,color);
        draw(24,9,color);
        draw(25,9,color);
        draw(26,9,color);
        draw(27,9,color);

        draw(24,5,color - 6); //face 3
        draw(27,5,color - 6);
        draw(24,2,color - 6);
        draw(25,3,color - 6);
        draw(26,3,color - 6);
        draw(27,2,color - 6);
    }
}

void draw_play_outline(uint8_t color) {
    draw_rect(1, 54, 30, 54, color);
    draw_rect(1, 35, 1, 54, color);
    draw_rect(1, 35, 10, 35, color);
    draw_rect(10, 36, 10, 45, color);
    draw_rect(10, 45, 30, 45, color);
    draw_rect(30, 45, 30, 54, color);
}

void draw_leaderboard_outline(uint8_t color) {
    draw_rect(12, 24, 30, 43, color);
    draw_rect(13, 25, 29, 42, 7);
}

void draw_music_outline(uint8_t color) {
    draw_rect(1, 14, 10, 33, color);
    draw_rect(1, 14, 19, 22, color);
    draw_rect(10, 6, 19, 22, color);
    draw_rect(2, 15, 9, 32, 7);
    draw_rect(2, 15, 18, 21, 7);
    draw_rect(11, 7, 18, 21, 7);
}

void draw_difficulty_outline(uint8_t color) {
    draw_rect(21, 0, 30, 22, color);
    draw_rect(22, 0, 29, 21, 7);
    draw_rect(22,7,29,7,color);
    draw_rect(22,14,29,14,color);
}

void draw_other_outline(uint8_t color) {
    draw_rect(1, 0, 8, 12, color);
    draw_rect(1, 0, 19, 4, color);
    draw_rect(2, 0, 7, 11, 7);
    draw_rect(2, 0, 18, 3, 7);
}


