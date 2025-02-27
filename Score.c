#include "stm32f0xx.h"
#include "stm32f0_discovery.h"
#include "constants.h"
#include "led_matrix.h"
#include "tetris.h"
#include "pieces.h"
#include "controller.h"

//points for 1 line = 40 * (n + 1) where n is the level number
//points for 2 line = 100 * (n + 1) where n is the level number
//points for 3 line = 300 * (n + 1) where n is the level number
//points for 4 line = 1200 * (n + 1) where n is the level number

int SCORE = 0;

void addScore (int amount)
{
	SCORE += amount;
}

int getScore ()
{
	return SCORE;
}

void initialize_symbols ()
{
    draw(3,12,2);
    draw_rect(2,11,4,11,2);
    draw_rect(1,10,5,10,2);
    draw_rect(3,8,3,9,2);

    draw(3,6,4);
    draw_rect(1,5,5,5,4);
    draw_rect(2,4,4,4,4);
    draw_rect(2,3,4,3,4);
    draw_rect(1,2,2,2,4);
    draw_rect(4,2,5,2,4);

//    draw_rect(7,12,10,12,6);
//    draw_rect(7,8,7,11,6);
//    draw_rect(8,8,10,8,6);
//    draw_rect(10,8,10,11,6);
//    draw_number(Zero,7,12,2);
//    draw_number(One,12,12,3);
//    draw_number(Two,17,12,4);
//    draw_number(Four,22,12,5);
//    draw_number(Five,27,12,1);
}

//void initialize_numbers ()
//{
//    draw_rect(7,12,10,12,6);
//    draw_rect(7,8,7,11,6);
//    draw_rect(8,8,10,8,6);
//    draw_rect(8,8,8,10,6);
//}


void draw_number(const uint8_t shape[5][4], int x, int y, int color)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 4; j++)
        {

            if(shape[i][j] == 1)
            {
                draw(j + x, -i + y, color);

            }
        }
    }
}

void draw_score(int score, int x, int y, int color)// x = 27, y = 12
{
	draw_rect(8, 7, 32, 12, 7);
//    int x = 27;
    int count = 0;
    while(score != 0)
    {
        int value = score % 10;
        switch(value)
        {
                    case 0:
                        draw_number(Zero,x,y,color);
                        x = x-5;
                        count += 1;
                        score /= 10;
                        break;
                    case 1:
                        draw_number(One,x,y,color);
                        x = x-5;
                        count += 1;
                        score /= 10;
                        break;
                    case 2:
                        draw_number(Two,x,y,color);
                        x = x-5;
                        count += 1;
                        score /= 10;
                        break;
                    case 3:
                        draw_number(Three,x,y,color);
                        x = x-5;
                        count += 1;
                        score /= 10;
                        break;
                    case 4:
                        draw_number(Four,x,y,color);
                        x = x-5;
                        count += 1;
                        score /= 10;
                        break;
                    case 5:
                        draw_number(Five,x,y,color);
                        x = x-5;
                        count += 1;
                        score /= 10;
                        break;
                    case 6:
                        draw_number(Six,x,y,color);
                        x = x-5;
                        count += 1;
                        score /= 10;
                        break;
                    case 7:
                        draw_number(Seven,x,y,color);
                        x = x-5;
                        count += 1;
                        score /= 10;
                        break;
                    case 8:
                        draw_number(Eight,x,y,color);
                        x = x-5;
                        count += 1;
                        score /= 10;
                        break;
                    case 9:
                        draw_number(Nine,x,y,color);
                        x = x-5;
                        count += 1;
                        score /= 10;
                        break;
        }



    }

    while(x>=7)
    {
        draw_number(Zero,x,y,color);
        x -=5;
    }
}

void draw_rank(int rank, int x, int y, int color)
{
	int count = 0;
	   while(rank != 0)
	    {
	        int value = rank % 10;
	        switch(value)
	        {
	                    case 0:
	                        draw_number(Zero,x,y,color);
	                        x = x-5;
	                        rank /= 10;
	                        count += 1;
	                        break;
	                    case 1:
	                        draw_number(One,x,y,color);
	                        x = x-5;
	                        rank /= 10;
	                        count += 1;
	                        break;
	                    case 2:
	                        draw_number(Two,x,y,color);
	                        x = x-5;
	                        rank /= 10;
	                        count += 1;
	                        break;
	                    case 3:
	                        draw_number(Three,x,y,color);
	                        x = x-5;
	                        rank /= 10;
	                        count += 1;
	                        break;
	                    case 4:
	                        draw_number(Four,x,y,color);
	                        x = x-5;
	                        rank /= 10;
	                        count += 1;
	                        break;
	                    case 5:
	                        draw_number(Five,x,y,color);
	                        x = x-5;
	                        rank /= 10;
	                        count += 1;
	                        break;
	                    case 6:
	                        draw_number(Six,x,y,color);
	                        x = x-5;
	                        rank /= 10;
	                        count += 1;
	                        break;
	                    case 7:
	                        draw_number(Seven,x,y,color);
	                        x = x-5;
	                        rank /= 10;
	                        count += 1;
	                        break;
	                    case 8:
	                        draw_number(Eight,x,y,color);
	                        x = x-5;
	                        rank /= 10;
	                        count += 1;
	                        break;
	                    case 9:
	                        draw_number(Nine,x,y,color);
	                        x = x-5;
	                        rank /= 10;
	                        count += 1;
	                        break;
	        }



	    }

	    while(count < 2)
	    {
	        draw_number(Zero,x,y,color);
	        count +=1;
	    }
}

void draw_level(int level)
{
    draw_rect(23, 45, 31, 50, 7);
    int x = 27;
    int count = 0;
    while(level != 0)
    {
        int value = level % 10;
        switch(value)
        {
                    case 0:
                        draw_number(Zero,x,50,2);
                        x = x-4;
                        count += 1;
                        level /= 10;
                        break;
                    case 1:
                        if(x != 27)
                        {
                            draw_number(One_t,x,50,2);
                        }
                        else{
                        draw_number(One,x,50,2);}

                        x = x-4;
                        count += 1;
                        level /= 10;
                        break;
                    case 2:
                        if(x != 27)
                        {
                            draw_number(Two_t,x,50,2);
                        }
                        else{
                        draw_number(Two,x,50,2);}

                        x = x-4;
                        count += 1;
                        level /= 10;
                        break;
                    case 3:
                        if(x != 27)
                        {
                            draw_number(Three_t,x,50,2);
                        }
                        else{
                        draw_number(Three,x,50,2);}

                        x = x-4;
                        count += 1;
                        level /= 10;
                        break;
                    case 4:
                        draw_number(Four,x,50,2);
                        x = x-4;
                        count += 1;
                        level /= 10;
                        break;
                    case 5:
                        draw_number(Five,x,50,2);
                        x = x-4;
                        count += 1;
                        level /= 10;
                        break;
                    case 6:
                        draw_number(Six,x,50,2);
                        x = x-4;
                        count += 1;
                        level /= 10;
                        break;
                    case 7:
                        draw_number(Seven,x,50,2);
                        x = x-4;
                        count += 1;
                        level /= 10;
                        break;
                    case 8:
                        draw_number(Eight,x,50,2);
                        x = x-4;
                        count += 1;
                        level /= 10;
                        break;
                    case 9:
                        draw_number(Nine,x,50,2);
                        x = x-4;
                        count += 1;
                        level /= 10;
                        break;
        }



    }

    while(x >= 23)
    {
        draw_number(Zero_t,x,50,2);
        x -=4;
    }



}

