/////////////////////////////////////////////////////////////////////////
// Game Programming All In One, Second Edition
// Source Code Copyright (C)2004 by Jonathan S. Harbour
// Tank War Enhancement 5 - tank.c
/////////////////////////////////////////////////////////////////////////

#include "tankwar.h"


void drawtank(int num)
{
    int dir = tanks[num]->dir;
    int x = tanks[num]->x-15;
    int y = tanks[num]->y-15;
    draw_sprite(buffer, tank_bmp[num][dir], x, y);

    //what about the enemy tank?
    x = scrollx[!num] + SCROLLW/2;
    y = scrolly[!num] + SCROLLH/2;
    if (inside(x, y, 
        scrollx[num], scrolly[num], 
        scrollx[num] + SCROLLW, scrolly[num] + SCROLLH))
    {
        //draw enemy tank, adjust for scroll
        draw_sprite(buffer, tank_bmp[!num][tanks[!num]->dir], 
            startx[num]+x-scrollx[num]-15, starty[num]+y-scrolly[num]-15);

    }
}

void movetank(int num){
    int dir = tanks[num]->dir;
    int speed = tanks[num]->xspeed;

    //update tank position
    switch(dir)
    {
        case 0:
            scrolly[num] -= speed;
            break;
        case 1:
            scrolly[num] -= speed;
            scrollx[num] += speed;
            break;
        case 2:
            scrollx[num] += speed;
            break;
        case 3:
            scrollx[num] += speed;
            scrolly[num] += speed;
            break;
        case 4:
            scrolly[num] += speed;
            break;
        case 5:
            scrolly[num] += speed;
            scrollx[num] -= speed;
            break;
        case 6:
            scrollx[num] -= speed;
            break;
        case 7:
            scrollx[num] -= speed;
            scrolly[num] -= speed;
            break;
    }

    //keep tank inside bounds
    if (scrollx[num] < 0)
        scrollx[num] = 0;
    if (scrollx[num] > scroll->w - SCROLLW)
        scrollx[num] = scroll->w - SCROLLW;
    if (scrolly[num] < 0)
        scrolly[num] = 0;
    if (scrolly[num] > scroll->h - SCROLLH)
        scrolly[num] = scroll->h - SCROLLH;

}
