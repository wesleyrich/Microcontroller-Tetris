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
void rick();
int check_gameover();
int check_collision_y(uint8_t shape [4][4]);
int check_collision_xpos(uint8_t shape [4][4]);
int check_collision_xneg(uint8_t shape [4][4]);

#endif /* TETRIS_H_ */
