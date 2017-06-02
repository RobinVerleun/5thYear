/////////////////////////////////////////////////////////////////////////
// Game Programming All In One, Third Edition
// Tank War Enhancement 7 - tank.c
/////////////////////////////////////////////////////////////////////////

#include "tankwar.h"

//new function added in chapter 11
void animatetank(int num)
{
    if (++tanks[num]->framecount > tanks[num]->framedelay)
    {
        tanks[num]->framecount = 0;
        tanks[num]->curframe += tanks[num]->animdir;
        if (tanks[num]->curframe > tanks[num]->maxframe)
            tanks[num]->curframe = 0;
        else if (tanks[num]->curframe < 0)
            tanks[num]->curframe = tanks[num]->maxframe;
    }
}

void drawtank(int num)
{
    int dir = tanks[num]->dir;
    int x = tanks[num]->x-15;
    int y = tanks[num]->y-15;
    draw_sprite(buffer, tank_bmp[num][tanks[num]->curframe][dir], x, y);

    //what about the enemy tank?
    x = scrollx[!num] + SCROLLW/2;
    y = scrolly[!num] + SCROLLH/2;
    if (inside(x, y, 
        scrollx[num], scrolly[num], 
        scrollx[num] + SCROLLW, scrolly[num] + SCROLLH))
    {
        //draw enemy tank, adjust for scroll
        draw_sprite(buffer, tank_bmp[!num][tanks[!num]->curframe][tanks[!num]->dir], 
            startx[num]+x-scrollx[num]-15, starty[num]+y-scrolly[num]-15);

    }
}

void movetank(int num)
{
    int dir = tanks[num]->dir;
    int speed = tanks[num]->xspeed;

    //animate tank when moving
    if (speed > 0) 
    {
        tanks[num]->animdir = 1;
        tanks[num]->framedelay = MAXSPEED - speed;
    }
    else if (speed < 0)
    {
        tanks[num]->animdir = -1;
        tanks[num]->framedelay = MAXSPEED - abs(speed);
    }
    else
        tanks[num]->animdir = 0;


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
    {
        scrollx[num] = 0;
        tanks[num]->xspeed = 0;
    }

    else if (scrollx[num] > mapwidth*mapblockwidth - SCROLLW)
    {
        scrollx[num] = mapwidth*mapblockwidth - SCROLLW;
        tanks[num]->xspeed = 0;
    }

    if (scrolly[num] < 0)
    {
        scrolly[num] = 0;
        tanks[num]->xspeed = 0;
    }
    else if (scrolly[num] > mapheight*mapblockheight - SCROLLH)
    {
        scrolly[num] = mapheight*mapblockheight - SCROLLH;
        tanks[num]->xspeed = 0;
    }

}
