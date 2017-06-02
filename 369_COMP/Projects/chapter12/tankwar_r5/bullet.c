/////////////////////////////////////////////////////////////////////////
// Game Programming All In One, Second Edition
// Source Code Copyright (C)2004 by Jonathan S. Harbour
// Tank War Enhancement 5 - bullet.c
/////////////////////////////////////////////////////////////////////////

#include "tankwar.h"


void explode(int num, int x, int y)
{
    int n;

    //load explode image
    if (explode_bmp == NULL)
    {
        explode_bmp = load_bitmap("explode.bmp", NULL);
    }
    
    //draw the explosion bitmap several times
    for (n = 0; n < 5; n++)
    {
        rotate_sprite(screen, explode_bmp, 
            x + rand()%10 - 20, y + rand()%10 - 20, 
            itofix(rand()%255));

        rest(30);
    }
}

void drawbullet(int num)
{
    int n;
    int x, y;

    x = bullets[num]->x;
    y = bullets[num]->y;

    //is the bullet active?
    if (!bullets[num]->alive) return;

    //draw bullet sprite
    for (n=0; n<2; n++)
    {
        if (inside(x, y, scrollx[n], scrolly[n], 
            scrollx[n] + SCROLLW - bullet_bmp->w, 
            scrolly[n] + SCROLLH - bullet_bmp->h))
            
            //draw bullet, adjust for scroll
            draw_sprite(buffer, bullet_bmp, startx[n] + x-scrollx[n], 
                starty[n] + y-scrolly[n]);
    }

    //draw bullet on radar
    putpixel(buffer, radarx + x/10, radary + y/12, WHITE);

}

void movebullet(int num)
{
    int x, y, tx, ty;

    x = bullets[num]->x;
    y = bullets[num]->y;

    //is the bullet active?
    if (!bullets[num]->alive) return;
    
    //move bullet
    bullets[num]->x += bullets[num]->xspeed;
    bullets[num]->y += bullets[num]->yspeed;
    x = bullets[num]->x;
    y = bullets[num]->y;

    //stay within the virtual screen
    if (x < 0 || x > MAPW-6 || y < 0 || y > MAPH-6)
    {
        bullets[num]->alive = 0;
        return;
    }

    //look for a direct hit using basic collision
    tx = scrollx[!num] + SCROLLW/2;
    ty = scrolly[!num] + SCROLLH/2;

    //if (collided(bullets[num], tanks[!num]))
    if (inside(x,y,tx-15,ty-15,tx+15,ty+15))
    {
        //kill the bullet
        bullets[num]->alive = 0;
            
        //blow up the tank
            x = scrollx[!num] + SCROLLW/2;
            y = scrolly[!num] + SCROLLH/2;

            if (inside(x, y, 
                scrollx[num], scrolly[num], 
                scrollx[num] + SCROLLW, scrolly[num] + SCROLLH))
            {
                //draw explosion in my window
                explode(num, startx[num]+x-scrollx[num], 
                    starty[num]+y-scrolly[num]);
            }

        //draw explosion in enemy window
        explode(num, tanks[!num]->x, tanks[!num]->y);
        scores[num]++;
    }
}

void fireweapon(int num)
{
    int x = scrollx[num] + SCROLLW/2;
    int y = scrolly[num] + SCROLLH/2;

    //ready to fire again?
    if (!bullets[num]->alive)
    {
        bullets[num]->alive = 1;

        //fire bullet in direction tank is facing
        switch (tanks[num]->dir)
        {
            //north
            case 0:
                bullets[num]->x = x-2;
                bullets[num]->y = y-22;
                bullets[num]->xspeed = 0;
                bullets[num]->yspeed = -BULLETSPEED;
                break;
            //NE
            case 1:
                bullets[num]->x = x+18;
                bullets[num]->y = y-18;
                bullets[num]->xspeed = BULLETSPEED;
                bullets[num]->yspeed = -BULLETSPEED;         
                break;  
            //east
            case 2:
                bullets[num]->x = x+22;
                bullets[num]->y = y-2;
                bullets[num]->xspeed = BULLETSPEED;
                bullets[num]->yspeed = 0;
                break;
            //SE
            case 3:
                bullets[num]->x = x+18;
                bullets[num]->y = y+18;
                bullets[num]->xspeed = BULLETSPEED;
                bullets[num]->yspeed = BULLETSPEED;
                break;
            //south
            case 4:
                bullets[num]->x = x-2;
                bullets[num]->y = y+22;
                bullets[num]->xspeed = 0;
                bullets[num]->yspeed = BULLETSPEED;
                break;
            //SW
            case 5:
                bullets[num]->x = x-18;
                bullets[num]->y = y+18;
                bullets[num]->xspeed = -BULLETSPEED;
                bullets[num]->yspeed = BULLETSPEED;
                break;
            //west
            case 6:
                bullets[num]->x = x-22;
                bullets[num]->y = y-2;
                bullets[num]->xspeed = -BULLETSPEED;
                bullets[num]->yspeed = 0;
                break;
            //NW
            case 7:
                bullets[num]->x = x-18;
                bullets[num]->y = y-18;
                bullets[num]->xspeed = -BULLETSPEED;
                bullets[num]->yspeed = -BULLETSPEED;
                break;
        }
    }
}
