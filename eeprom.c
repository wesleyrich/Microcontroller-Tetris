/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f0xx.h"
#include "stm32f0_discovery.h"
#include "eeprom.h"

#define FAIL -1
#define SUCCESS 0
#define WR 0
#define RD 1

uint32_t names [25];
uint32_t highscores [25];


uint32_t get_name (int index)
{
    return names[index];
}

uint32_t get_highscores (int index)
{
    return highscores[index];
}


void read_and_sort()
{
    for (int i = 0; i < 50; i += 2)
    {
        names[i / 2] = read_EEPROM(i * 4);
        highscores[i / 2] = read_EEPROM((i + 1) * 4);
    }

    int i, key1, key2, j;
    for (i = 1; i < 25; i++)
    {
        key1 = highscores[i];
        key2 = names[i];
        j = i - 1;

        /* Move elements of arr[0..i-1], that are
        greater than key, to one position ahead
        of their current position */
        while (j >= 0 && highscores[j] < key1)
        {
            highscores[j + 1] = highscores[j];
            names[j+1] = names[j];
            j = j - 1;
        }
        highscores[j + 1] = key1;
        names [j+1] = key2;
    }

}

void I2C1_waitidle() {
    while((I2C1->ISR & I2C_ISR_BUSY) == I2C_ISR_BUSY);
}

int I2C1_checknack() {
    if(I2C1->ISR & I2C_ISR_NACKF) return 1;
    return 0;
}

void I2C1_clearnack() {
    I2C1->ICR |= I2C_ICR_NACKCF;
}

void initialize_eeprom() {
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
    GPIOB->MODER &= ~(GPIO_MODER_MODER6 | GPIO_MODER_MODER7);
    GPIOB->MODER |= GPIO_MODER_MODER6_1 | GPIO_MODER_MODER7_1;
    GPIOB->AFR[0] |= (1 << 24) | (1 << 28);  // Configuring PB6/7 to AF1

    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
    I2C1->CR2 &= ~I2C_CR2_ADD10;  // Setting to 7-bit mode
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
}

void I2C1_start(uint8_t addr, uint32_t dir) {
    I2C1->CR2 &= ~(I2C_CR2_SADD | I2C_CR2_NBYTES | I2C_CR2_RELOAD | I2C_CR2_AUTOEND | I2C_CR2_RD_WRN | I2C_CR2_START | I2C_CR2_STOP);
    I2C1->CR2 |= addr << 1;
    if(dir == RD) I2C1->CR2 |= I2C_CR2_RD_WRN;
    I2C1->CR2 |= I2C_CR2_START;
}

void I2C1_stop() {
    if((I2C1->ISR & I2C_ISR_STOPF) == I2C_ISR_STOPF) return;
    I2C1->CR2 |= I2C_CR2_STOP;
    while((I2C1->ISR & I2C_ISR_STOPF) != I2C_ISR_STOPF);
    I2C1->ICR |= I2C_ICR_STOPCF;
}

int I2C1_senddata(uint8_t* data, uint32_t size) {
    I2C1->CR2 &= ~I2C_CR2_NBYTES;
    I2C1->CR2 |= size << 16; //NBYTES = size

    for(int i=0; i<size; i++)
    {
        int timeout = 0;
        while((I2C1->ISR & I2C_ISR_TXIS) == 0)
        {
            timeout++;
            if(timeout > 1000000)
                return FAIL;
        }
        I2C1->TXDR = data[i];
    }

    while(((I2C1->ISR & I2C_ISR_TC) != I2C_ISR_TC) && ((I2C1->ISR & I2C_ISR_NACKF) != I2C_ISR_NACKF));
    if((I2C1->ISR & I2C_ISR_NACKF) == I2C_ISR_NACKF)
        return FAIL;

    return SUCCESS;
}

int I2C1_readdata(uint8_t* data, uint32_t size) {
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
}

void write_EEPROM(uint16_t wr_addr, uint32_t data) {
    uint8_t data0 = data & 0xff;
    uint8_t data1 = (data >> 8) & 0xff;
    uint8_t data2 = (data >> 16) & 0xff;
    uint8_t data3 = data >> 24;
    uint8_t write_buf[6] = {(wr_addr>>8) & 0x00FF, wr_addr & 0x00FF, data3, data2, data1, data0};
    I2C1_waitidle();
    I2C1_start(0x50, WR);
    int status = I2C1_senddata(write_buf, 6);
    I2C1_stop();
    nano_wait(5000000);
}

uint32_t read_EEPROM(uint16_t rd_addr) {
    uint8_t data[4];
    uint8_t write_buf[2] = {(rd_addr>>8) & 0x00FF, rd_addr & 0x00FF};
    I2C1_waitidle();
    I2C1_start(0x50, WR);
    int status = I2C1_senddata(write_buf, 2);
    //if (status == FAIL) while(1);
    I2C1_start(0x50, RD);
    status = I2C1_readdata(data, 4);
    //if (status == FAIL) while(1);
    I2C1_stop();
    uint32_t frankensteined_data = (uint32_t) (data[3] + (data[2] << 8) + (data[1] << 16) + (data[0] << 24));
    if (status == 0) return frankensteined_data;  // if read was successful
    return FAIL;
}
