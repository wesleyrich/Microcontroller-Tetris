/*
 * led_matrix.h
 *
 *  Created on: Nov 7, 2019
 *      Author: gjulian
 */

#ifndef LED_MATRIX_H_
#define LED_MATRIX_H_

int toggle_bit_c(int code);
void set_bit_c(int code, int state);
void set_row(int row);
void update_led();
void set_color(uint8_t channel, uint8_t color);
void nano_wait(unsigned int n);
void draw(int x, int y, int color);
void draw_rect(int x1, int y1, int x2, int y2, uint8_t color);
void initialize_pixels();
void LED_pins_setup ();
int getPixels (int x, int y);
void draw_piece(uint8_t shape [4][4], int x, int y, int color);


#endif /* LED_MATRIX_H_ */
