#include "stm32f0xx.h"
#include "stm32f0_discovery.h"
#include "constants.h"
#include "led_matrix.h"
#include "tetris.h"
#include "pieces.h"
#include "controller.h"

#define FAIL -1
#define SUCCESS 0
#define WR 0
#define RD 1

void I2C1_waitidle(void) {
    while ((I2C1->ISR & I2C_ISR_BUSY) == I2C_ISR_BUSY);  // while busy, wait.
}

int I2C1_checknack(void) {
    if (I2C1->ISR & I2C_ISR_NACKF)
        return 1;
    return 0;
}

void I2C1_clearnack(void) {
    I2C1->ICR |= I2C_ICR_NACKCF;
}

void init_I2C1() {
    // Student code goes here
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

	// Configuring PB6/7 to AF1
	GPIOB->MODER &= ~(GPIO_MODER_MODER6 | GPIO_MODER_MODER7);
	GPIOB->MODER |= GPIO_MODER_MODER6_1 | GPIO_MODER_MODER7_1;
	GPIOB->AFR[0] |= (1 << 24) | (1 << 28);

	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;

	// Setting to 7-bit mode and enable NACK
	I2C1->CR2 &= ~I2C_CR2_ADD10;
	I2C1->CR2 |= I2C_CR2_NACK;

	I2C1->TIMINGR = 0;
	I2C1->TIMINGR &= ~I2C_TIMINGR_PRESC;
	I2C1->TIMINGR |= 4 << 28; //PRESC
	I2C1->TIMINGR |= 3 << 20; //SCLDEL
	I2C1->TIMINGR |= 1 << 16; //SDADEL
	I2C1->TIMINGR |= 3 << 8; //SCLH
	I2C1->TIMINGR |= 9 << 0; //SCLL

	// Disable own address1 and own address 2, then set the 7 bit own address to 1.
	I2C1->OAR1 &= ~I2C_OAR1_OA1EN;
	I2C1->OAR2 &= ~I2C_OAR2_OA2EN;
	I2C1->OAR1 = I2C_OAR1_OA1EN | 0x2;

	I2C1->CR1 |= I2C_CR1_PE;
    //---------End-----------
}

void I2C1_start(uint8_t addr, uint32_t dir) {
    // Student code goes here
	I2C1->CR2 &= ~(I2C_CR2_SADD | I2C_CR2_NBYTES | I2C_CR2_RELOAD | I2C_CR2_AUTOEND | I2C_CR2_RD_WRN | I2C_CR2_START | I2C_CR2_STOP);
	I2C1->CR2 |= addr << 1;
	if(dir == RD) I2C1->CR2 |= I2C_CR2_RD_WRN;
	I2C1->CR2 |= I2C_CR2_START;
    //---------End-----------
}

void I2C1_stop() {
    // Student code goes here
	if((I2C1->ISR & I2C_ISR_STOPF) == I2C_ISR_STOPF) return;
	I2C1->CR2 |= I2C_CR2_STOP;
	while((I2C1->ISR & I2C_ISR_STOPF) != I2C_ISR_STOPF);
	I2C1->ICR |= I2C_ICR_STOPCF;
    //---------End-----------
}

int I2C1_senddata(uint8_t* data, uint32_t size) {
    // Student code goes here
	I2C1->CR2 &= ~I2C_CR2_NBYTES;
	I2C1->CR2 |= size << 16; //NBYTES = size

	for(int i=0; i<size; i++)
	{
		int timeout = 0;
		while((I2C1->ISR & I2C_ISR_TXIS) == 0)
		{
			timeout++;
			if(timeout > 1000000) return FAIL;
		}
		I2C1->TXDR = data[i];
	}

	while(((I2C1->ISR & I2C_ISR_TC) != I2C_ISR_TC) && ((I2C1->ISR & I2C_ISR_NACKF) != I2C_ISR_NACKF));
	if((I2C1->ISR & I2C_ISR_NACKF) == I2C_ISR_NACKF) return FAIL;

	return SUCCESS;
    //---------End-----------
}

int I2C1_readdata(int8_t* data, uint32_t size) {
    // Student code goes here
	I2C1->CR2 &= ~I2C_CR2_NBYTES;
	I2C1->CR2 |= size << 16; //NBYTES = size

	for(int i=0; i<size; i++)
	{
		int timeout = 0;
		while((I2C1->ISR & I2C_ISR_RXNE) != I2C_ISR_RXNE)
		{
			timeout++;
			if(timeout > 1000000) return FAIL;
		}
		 data[i] = I2C1->RXDR;
	}

	while(((I2C1->ISR & I2C_ISR_TC) != I2C_ISR_TC) && ((I2C1->ISR & I2C_ISR_NACKF) != I2C_ISR_NACKF));
	if((I2C1->ISR & I2C_ISR_NACKF) == I2C_ISR_NACKF) return FAIL;

	return SUCCESS;
    //---------End-----------
}

void write_EEPROM(uint16_t wr_addr, uint8_t data) {
    // Student code goes here
	uint8_t write_buf[3] = {(wr_addr>>8) & 0x00FF, wr_addr & 0x00FF, data};
	I2C1_waitidle();
	I2C1_start(0x50, WR);
	I2C1_senddata(write_buf, 3);
	I2C1_stop();
	nano_wait(5000000);
    //---------End-----------
}

uint8_t read_EEPROM(uint16_t rd_addr) {
	uint8_t read_buf[2] = {(rd_addr>>8) & 0x00FF, rd_addr & 0x00FF};
	uint8_t data = 0;
	I2C1_waitidle();
	I2C1_start(0x50, RD);
	I2C1_senddata(&read_buf, 2);
	I2C1_readdata(&data, 1);
	I2C1_stop();
	nano_wait(5000000);
	return data;
}
