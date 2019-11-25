/*
 * menu.h
 *
 *  Created on: Nov 13, 2019
 *      Author: gjulian
 */

#ifndef MINIPROJECT_MENU_H_
#define MINIPROJECT_MENU_H_

void initialize_menu();
void change_selected();
void handle_input_menu();
void draw_difficulty();
int get_difficulty();
void draw_play_outline(uint8_t color);
void draw_leaderboard_outline (uint8_t color);
void draw_music_outline (uint8_t color);
void draw_difficulty_outline (uint8_t color);
void draw_other_outline(uint8_t color);
int  get_music_state();
void set_music_state(int state);

#endif /* MINIPROJECT_MENU_H_ */
