/////////////////////////////////////////////////////////////////////////
// Game Programming All In One, Third Edition
// Tank War Enhancement 7 - input.c
/////////////////////////////////////////////////////////////////////////

#include "tankwar.h"

void forward(int num)
{
    //use xspeed as a generic "speed" variable
    tanks[num]->xspeed++;
    if (tanks[num]->xspeed > MAXSPEED)
        tanks[num]->xspeed = MAXSPEED;
}

void backward(int num)
{
    tanks[num]->xspeed--;
    if (tanks[num]->xspeed < -MAXSPEED)
        tanks[num]->xspeed = -MAXSPEED;
}

void turnleft(int num)
{
    tanks[num]->dir--;
    if (tanks[num]->dir < 0)
        tanks[num]->dir = 7;
}

void turnright(int num)
{
    tanks[num]->dir++;
    if (tanks[num]->dir > 7)
        tanks[num]->dir = 0;
}

void getinput()
{
    //hit ESC to quit
    if (key[KEY_ESC])   gameover = 1;

    //WASD - SPACE keys control tank 1
    if (key[KEY_W])     forward(0);
    if (key[KEY_D])     turnright(0);
    if (key[KEY_A])     turnleft(0);
    if (key[KEY_S])     backward(0);
    if (key[KEY_SPACE]) fireweapon(0);

    //arrow - ENTER keys control tank 2
    if (key[KEY_UP])    forward(1);
    if (key[KEY_RIGHT]) turnright(1);
    if (key[KEY_DOWN])  backward(1);
    if (key[KEY_LEFT])  turnleft(1);
    if (key[KEY_ENTER]) fireweapon(1);

    //short delay after keypress
    rest(20);

}

