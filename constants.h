/*
 * constants.h
 *
 *  Created on: Nov 7, 2019
 *      Author: gjulian
 */

#include "stdint.h"

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

// TIMING STUFF
#define TIM2_FREQ 10000 // 12 MHz

// Controller buttons
// A B sel start up down left right
#define but_A 7
#define but_B 6
#define but_SEL 5
#define but_START 4
#define but_UP 3
#define but_DOWN 2
#define but_LEFT 1
#define but_RIGHT 0

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

// PIN NUMBERS IN GPIOA
#define CTRL_CLK 0
#define CTRL_LAT 1
#define CTRL_DAT 2

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

//s
static const uint8_t S0[4][4] = {{0,1,1,0}, {1,1,0,0}, {0,0,0,0}, {0,0,0,0}}; //0 rotations s
static const uint8_t S1[4][4] = {{1,0,0,0}, {1,1,0,0}, {0,1,0,0}, {0,0,0,0}}; //1 rotations s
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
static const uint8_t Eight[5][4] = {{1,1,1,1}, {1,0,0,1}, {1,1,1,1}, {1,0,0,1}, {1,1,1,1}};

//9
static const uint8_t Nine[5][4] = {{1,1,1,1}, {1,0,0,1}, {1,1,1,1}, {0,0,0,1}, {0,0,0,1}};


//tens place
//1
static const uint8_t Zero_t[5][4] = {{1,1,1,0}, {1,0,1,0}, {1,0,1,0}, {1,0,1,0}, {1,1,1,0}};
static const uint8_t One_t[5][4] = {{1,1,0,0},{0,1,0,0}, {0,1,0,0}, {0,1,0,0}, {1,1,1,0}};
static const uint8_t Two_t[5][4] = {{1,1,1,0},{0,0,1,0}, {1,1,1,0}, {1,0,0,0}, {1,1,1,0}};
static const uint8_t Three_t[5][4] = {{1,1,1,0},{0,0,1,0}, {1,1,1,0}, {0,0,1,0}, {1,1,1,0}};

// LETTERS
static const uint8_t letter_a[5][4] = {{0,1,1,0}, {1,0,0,1}, {1,1,1,1}, {1,0,0,1}, {1,0,0,1}};
static const uint8_t letter_b[5][4] = {{1,1,1,0}, {1,0,0,1}, {1,1,1,0}, {1,0,0,1}, {1,1,1,0}};
static const uint8_t letter_c[5][4] = {{0,1,1,1}, {1,0,0,0}, {1,0,0,0}, {1,0,0,0}, {0,1,1,1}};
static const uint8_t letter_d[5][4] = {{1,1,1,0}, {1,0,0,1}, {1,0,0,1}, {1,0,0,1}, {1,1,1,0}};
static const uint8_t letter_e[5][4] = {{1,1,1,1}, {1,0,0,0}, {1,1,1,0}, {1,0,0,0}, {1,1,1,1}};
static const uint8_t letter_f[5][4] = {{1,1,1,1}, {1,0,0,0}, {1,1,1,0}, {1,0,0,0}, {1,0,0,0}};
static const uint8_t letter_g[5][4] = {{1,1,1,1}, {1,0,0,0}, {1,0,1,1}, {1,0,0,1}, {1,1,1,1}};
static const uint8_t letter_h[5][4] = {{1,0,0,1}, {1,0,0,1}, {1,1,1,1}, {1,0,0,1}, {1,0,0,1}};
static const uint8_t letter_i[5][4] = {{0,1,1,1}, {0,0,1,0}, {0,0,1,0}, {0,0,1,0}, {0,1,1,1}};
static const uint8_t letter_j[5][4] = {{1,1,1,1}, {0,0,1,0}, {0,0,1,0}, {1,0,1,0}, {0,1,0,0}};
static const uint8_t letter_k[5][4] = {{1,0,0,1}, {1,0,1,0}, {1,1,0,0}, {1,0,1,0}, {1,0,0,1}};
static const uint8_t letter_l[5][4] = {{1,0,0,0}, {1,0,0,0}, {1,0,0,0}, {1,0,0,0}, {1,1,1,1}};
static const uint8_t letter_m[5][4] = {{1,0,0,1}, {1,0,1,1}, {1,0,0,1}, {1,0,0,1}, {1,0,0,1}};
static const uint8_t letter_n[5][4] = {{1,0,0,1}, {1,1,0,1}, {1,0,1,1}, {1,0,0,1}, {1,0,0,1}};
static const uint8_t letter_o[5][4] = {{1,1,1,1}, {1,0,0,1}, {1,0,0,1}, {1,0,0,1}, {1,1,1,1}};
static const uint8_t letter_p[5][4] = {{1,1,1,1}, {1,0,0,1}, {1,1,1,1}, {1,0,0,0}, {1,0,0,0}};
static const uint8_t letter_q[5][4] = {{1,1,1,1}, {1,0,0,1}, {1,0,0,1}, {1,0,1,1}, {1,1,1,1}};
static const uint8_t letter_r[5][4] = {{1,1,1,1}, {1,0,0,1}, {1,1,1,1}, {1,0,1,0}, {1,0,0,1}};
static const uint8_t letter_s[5][4] = {{0,1,1,1}, {1,0,0,0}, {0,1,1,0}, {0,0,0,1}, {1,1,1,0}};
static const uint8_t letter_t[5][4] = {{1,1,1,1}, {0,0,1,0}, {0,0,1,0}, {0,0,1,0}, {0,0,1,0}};
static const uint8_t letter_u[5][4] = {{1,0,0,1}, {1,0,0,1}, {1,0,0,1}, {1,0,0,1}, {0,1,1,0}};
static const uint8_t letter_v[5][4] = {{0,1,0,1}, {0,1,0,1}, {0,1,0,1}, {0,1,0,1}, {0,0,1,0}};
static const uint8_t letter_w[5][4] = {{1,0,0,1}, {1,0,0,1}, {1,0,0,1}, {1,1,1,1}, {1,0,0,1}};
static const uint8_t letter_x[5][4] = {{1,0,0,1}, {1,0,0,1}, {0,1,1,0}, {1,0,0,1}, {1,0,0,1}};
static const uint8_t letter_y[5][4] = {{1,0,0,1}, {1,0,0,1}, {1,1,1,1}, {0,0,0,1}, {1,1,1,1}};
static const uint8_t letter_z[5][4] = {{1,1,1,1}, {0,0,0,1}, {0,0,1,0}, {0,1,0,0}, {1,1,1,1}};
static const uint8_t letter_exclamation[5][4] = {{0,0,1,0}, {0,0,1,0}, {0,0,1,0}, {0,0,0,0}, {0,0,1,0}};
static const uint8_t letter_question[5][4] = {{0,1,1,0}, {0,0,0,1}, {0,0,1,0}, {0,0,0,0}, {0,0,1,0}};


#endif /* CONSTANTS2_H_*/
