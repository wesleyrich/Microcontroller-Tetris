#include "stm32f0xx.h"
#include "stm32f0_discovery.h"
#include "constants.h"
#include "led_matrix.h"
#include "tetris.h"
#include "pieces.h"

//points for 1 line = 40 * (n + 1) where n is the level number
//points for 2 line = 100 * (n + 1) where n is the level number
//points for 3 line = 300 * (n + 1) where n is the level number
//points for 4 line = 1200 * (n + 1) where n is the level number

void initialize_symbols ()
{
    draw(3,12,6);
    draw_rect(2,11,4,11,6);
    draw_rect(1,10,5,10,6);
    draw_rect(3,8,3,9,6);


}
