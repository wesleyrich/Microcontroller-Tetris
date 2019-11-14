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
void draw_play_outline(uint8_t color);
void draw_leaderboard_outline (uint8_t color);
void draw_music_outline (uint8_t color);
void draw_credits_outline (uint8_t color);
void draw_other_outline(uint8_t color);

#endif /* MINIPROJECT_MENU_H_ */
