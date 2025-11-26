
#include <time.h>
#include "SnakeTest.h"
#include <cstdlib>


int MAX_WIDTH=30,MAX_HEIGHT=20;
static int size=16;
static int width = size*MAX_WIDTH;
static int height = size*MAX_HEIGHT;
int fruitXPos, fruitYPos = 10;
int const MIN_SQUARE = 0; 



int dir,num=4;

struct Position 
{
    int x,y;
}  
square[100], fruit;
 

bool SnakeTest::moveSnake()
{
    for (int i = num; i > 0; --i)
    {
        square[i].x = square[i - 1].x;
        square[i].y = square[i - 1].y;
    } // move snake segments

    switch (dir)
    {
    case(0):
        square[MIN_SQUARE].y += 1;
        return true;

    case(1):
        square[MIN_SQUARE].x -= 1;
        return true;

    case(2):
        square[MIN_SQUARE].x += 1;
        return true;

    case(3):
        square[MIN_SQUARE].y -= 1;
        return true;

    default:
        return false;

    }
}


int SnakeTest::checkBounds(int t_x, int t_y)
{
    if (t_x > MAX_WIDTH)
    {
        t_x = 0;
        square[MIN_SQUARE].x = 0;
        return t_x;
    }
    if (t_x < 0)
    {
        t_x = MAX_WIDTH;
        square[MIN_SQUARE].x = MAX_WIDTH;
        return t_x;
    }
    if (t_y > MAX_HEIGHT)
    {
        t_y = 0;
        square[MIN_SQUARE].y = 0;
        return t_y;
    }
    if (t_y < 0)
    {
        t_y = MAX_HEIGHT;
        square[MIN_SQUARE].y = MAX_HEIGHT;
        return t_y;
    }
    return -1;
}

void Tick()
 {
    SnakeTest test;
    test.moveSnake();

    if ((square[MIN_SQUARE].x==fruit.x) && (square[MIN_SQUARE].y==fruit.y)) 
    {
        num++; // increase snake length?
        fruit.x=rand()%MAX_WIDTH;
        fruit.y=rand()%MAX_HEIGHT;
    }

    
    test.checkBounds(square[MIN_SQUARE].x, square[MIN_SQUARE].y);
    //Boundary Check

 
    for (int i=1;i<num;i++)
     if (square[MIN_SQUARE].x==square[i].x && square[MIN_SQUARE].y==square[i].y)
         num=i; // snake collision?
 }





int snake()
{  
    srand(time(0));
    Tick();
    
    float timer=0, delay=0.1;

    fruit.x=fruitXPos;
    fruit.y=fruitYPos; 
    
    



    return 0;
}


