/*
 * controller.h
 *
 *  Created on: Nov 11, 2019
 *      Author: rich27
 */

#ifndef MINIPROJECT_CONTROLLER_H_
#define MINIPROJECT_CONTROLLER_H_

void initialize_controller();
void set_bit_a(uint8_t code, uint8_t state);
uint8_t toggle_bit_a(uint8_t code);
void update_controller();
uint8_t get_buttons(uint8_t button);
uint8_t get_buttons_held(uint8_t button);
void clear_buttons();

#endif /* MINIPROJECT_CONTROLLER_H_ */
