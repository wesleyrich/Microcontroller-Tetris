/*
 * eeprom.h
 *
 *  Created on: Nov 15, 2019
 *      Author: rich27
 */

#ifndef MINIPROJECT_EEPROM_H_
#define MINIPROJECT_EEPROM_H_

void I2C1_waitidle(void);
int I2C1_checknack(void);
void I2C1_clearnack(void);
void initialize_eeprom(void);
void I2C1_start(uint8_t addr, uint32_t dir);
void I2C1_stop(void);
int I2C1_senddata(uint8_t* data, uint32_t size);
int I2C1_readdata(uint8_t* data, uint32_t size);
void write_EEPROM(uint16_t wr_addr, uint32_t data);
uint32_t read_EEPROM(uint16_t rd_addr);
void read_and_sort();
uint32_t get_highscores (int index);
uint32_t get_name (int index);

#endif /* MINIPROJECT_EEPROM_H_ */
