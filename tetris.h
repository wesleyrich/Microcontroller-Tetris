/*
 * tetris.h
 *
 *  Created on: Nov 7, 2019
 *      Author: gjulian
 */

#ifndef TETRIS_H_
#define TETRIS_H_

int LFSR(int init);
int get_piece();
void update_tetris();
void initialize_game();
void update_piece();
void spawn_piece();

#endif /* TETRIS_H_ */
