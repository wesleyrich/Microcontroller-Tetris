/*
 * state_manager.c
 *
 *  Created on: Nov 13, 2019
 *      Author: gjulian
 */
#include "state_manager.h"
#include "tetris.h"
#include "menu.h"

int state = 0; // current state of the program

// state 0 is menu
// state 1 is game
// ...

int getState() {
    return state;
}

void setState(int newstate) {
    state = newstate;
    switch (state)
    {
    case 0:
        initialize_menu();
        break;
    case 1:
        initialize_game();
        break;
    case 2:
    	initialize_leaderboard();
    	break;
    case 3:
        //initialize_volume();
        break;
    case 4:
        break;
    case 5:
        initialize_gameover();
        break;
    }
}
