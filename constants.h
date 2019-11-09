/*
 * constants.h
 *
 *  Created on: Nov 7, 2019
 *      Author: gjulian
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

// TIMING STUFF
#define TIM2_FREQ 500000 // 12 MHz

// PIN NUMBERS IN GPIOC
#define LED_OE 0
#define LED_CLK 1
#define LED_C 2
#define LED_A 3
#define LED_B2 4
#define LED_R2 5
#define LED_B1 6
#define LED_R1 7
#define LED_LAT 8
#define LED_D 9
#define LED_B 10
#define LED_G2 11
#define LED_G1 12

// COLORS
#define C_OFF -1
#define C_R 0
#define C_B 1
#define C_G 2
#define C_RB 3
#define C_RG 4
#define C_GB 5
#define C_RGB 6
// TETROMINOS

//top left pixel is start goes from top row to bottom row, 0 2x2 is on right

//I
static const uint8_t I0[4][4] = {{1,1,1,1}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}}; //0 rotations I
static const uint8_t I1[4][4] = {{1,0,0,0}, {1,0,0,0}, {1,0,0,0}, {1,0,0,0}}; //1 rotations I
static const uint8_t I2[4][4] = {{1,1,1,1}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}}; //2 rotations I
static const uint8_t I3[4][4] = {{1,0,0,0}, {1,0,0,0}, {1,0,0,0}, {1,0,0,0}}; //3 rotations I

//T
static const uint8_t T0[4][4] = {{1,1,1,0}, {0,1,0,0}, {0,0,0,0}, {0,0,0,0}}; //0 rotation T
static const uint8_t T1[4][4] = {{0,1,0,0}, {1,1,0,0}, {0,1,0,0}, {0,0,0,0}}; //1 rotation T
static const uint8_t T2[4][4] = {{0,1,0,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0}}; //2 rotations T
static const uint8_t T3[4][4] = {{1,0,0,0}, {1,1,0,0}, {1,0,0,0}, {0,0,0,0}}; //3 rotations T

//0
static const uint8_t O0[4][4] = {{1,1,0,0}, {1,1,0,0}, {0,0,0,0}, {0,0,0,0}}; //0 rotations O
static const uint8_t O1[4][4] = {{1,1,0,0}, {1,1,0,0}, {0,0,0,0}, {0,0,0,0}}; //1 rotations O
static const uint8_t O2[4][4] = {{1,1,0,0}, {1,1,0,0}, {0,0,0,0}, {0,0,0,0}}; //2 rotations O
static const uint8_t O3[4][4] = {{1,1,0,0}, {1,1,0,0}, {0,0,0,0}, {0,0,0,0}}; //3 rotations O

//l
static const uint8_t L0[4][4] = {{1,1,1,0}, {1,0,0,0}, {0,0,0,0}, {0,0,0,0}}; //0 rotations l
static const uint8_t L1[4][4] = {{1,1,0,0}, {0,1,0,0}, {0,1,0,0}, {0,0,0,0}}; //1 rotations l
static const uint8_t L2[4][4] = {{0,0,1,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0}}; //2 rotations l
static const uint8_t L3[4][4] = {{1,0,0,0}, {1,0,0,0}, {1,1,0,0}, {0,0,0,0}}; //3 rotations l

//j
static const uint8_t J0[4][4] = {{1,1,1,0}, {0,0,1,0}, {0,0,0,0}, {0,0,0,0}}; //0 rotations j
static const uint8_t J1[4][4] = {{0,1,0,0}, {0,1,0,0}, {1,1,0,0}, {0,0,0,0}}; //1 rotations j
static const uint8_t J2[4][4] = {{1,0,0,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0}}; //2 rotations j
static const uint8_t J3[4][4] = {{1,1,0,0}, {1,0,0,0}, {1,0,0,0}, {0,0,0,0}}; //3 rotations j

//z
static const uint8_t Z0[4][4] = {{1,1,0,0}, {0,1,1,0}, {0,0,0,0}, {0,0,0,0}}; //0 rotations z
static const uint8_t Z1[4][4] = {{0,1,0,0}, {1,1,0,0}, {1,0,0,0}, {0,0,0,0}}; //1 rotations z
static const uint8_t Z2[4][4] = {{1,1,0,0}, {0,1,1,0}, {0,0,0,0}, {0,0,0,0}}; //2 rotations z
static const uint8_t Z3[4][4] = {{0,1,0,0}, {1,1,0,0}, {1,0,0,0}, {0,0,0,0}}; //3 rotations z

//z
static const uint8_t S0[4][4] = {{0,1,1,0}, {1,1,0,0}, {0,0,0,0}, {0,0,0,0}}; //0 rotations s
static const uint8_t S1[4][4] = {{1,0,0,0}, {1,1,0,0}, {0,0,1,0}, {0,0,0,0}}; //1 rotations s
static const uint8_t S2[4][4] = {{0,1,1,0}, {1,1,0,0}, {0,0,0,0}, {0,0,0,0}}; //2 rotations s
static const uint8_t S3[4][4] = {{1,0,0,0}, {1,1,0,0}, {0,1,0,0}, {0,0,0,0}}; //3 rotations s

//0
static const uint8_t Zero[5][4] = {{1,1,1,1}, {1,0,0,1}, {1,0,0,1}, {1,0,0,1}, {1,1,1,1}};

//1
static const uint8_t One[5][4] = {{0,1,1,0}, {0,0,1,0}, {0,0,1,0}, {0,0,1,0}, {0,1,1,1}};

//2
static const uint8_t Two[5][4] = {{1,1,1,1}, {0,0,0,1}, {1,1,1,1}, {1,0,0,0}, {1,1,1,1}};

//3
static const uint8_t Three[5][4] = {{1,1,1,1}, {0,0,0,1}, {0,1,1,1},{0,0,0,1}, {1,1,1,1}};

//4
static const uint8_t Four[5][4] = {{1,0,1,0}, {1,0,1,0}, {1,1,1,1}, {0,0,1,0}, {0,0,1,0}};

//5
static const uint8_t Five[5][4] = {{1,1,1,1}, {1,0,0,0}, {1,1,1,1}, {0,0,0,1}, {1,1,1,1}};

//6
static const uint8_t Six[5][4] = {{1,1,1,1}, {1,0,0,0}, {1,1,1,1}, {1,0,0,1}, {1,1,1,1}};

//7
static const uint8_t Seven[5][4] = {{1,1,1,1},{1,0,0,1},{0,0,0,1}, {0,0,0,1}, {0,0,0,1}};

//8
static const uint8_t Eight[5][4] = {{1,1,1,1}, {1.0,0,1}, {1,1,1,1}, {1,0,0,1}, {1,1,1,1}};

//9
static const uint8_t Nine[5][4] = {{1,1,1,1}, {1,0,0,1}, {1,1,1,1}, {0,0,0,1}, {0,0,0,1}};



#endif /* CONSTANTS2_H_*/
