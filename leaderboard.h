/*
 * leaderboard.h
 *
 *  Created on: Nov 23, 2019
 *      Author: rich27
 */
#include "stdint.h"

#ifndef MINIPROJECT_LEADERBOARD_H_
#define MINIPROJECT_LEADERBOARD_H_

void initialize_leaderboard();
void handle_input_leaderboard();
void draw_letter(uint8_t letter[5][4], int x, int y, int color);

#endif /* MINIPROJECT_LEADERBOARD_H_ */
