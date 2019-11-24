/*
 * Score.h
 *
 *  Created on: Nov 8, 2019
 *      Author: gjulian
 */

#ifndef MINIPROJECT_SCORE_H_
#define MINIPROJECT_SCORE_H_

void initialize_symbols ();
void draw_score(int score, int x, int y, int color);
void draw_level(int level);
void addScore (int amount);
int getScore ();

#endif /* MINIPROJECT_SCORE_H_ */
