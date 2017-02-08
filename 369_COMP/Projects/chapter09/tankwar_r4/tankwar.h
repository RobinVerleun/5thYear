/////////////////////////////////////////////////////////////////////////
// Game Programming All In One, Third Edition
// Chapter 9 - Tank War Header (Enhancement 4)
/////////////////////////////////////////////////////////////////////////

#ifndef _TANKWAR_H
#define _TANKWAR_H

#include "allegro.h"

//define some game constants
#define MODE GFX_AUTODETECT_WINDOWED
#define WIDTH 640
#define HEIGHT 480
#define MAXSPEED 2
#define BULLETSPEED 6

//define some colors
#define TAN makecol(255,242,169)
#define BURST makecol(255,189,73)
#define BLACK makecol(0,0,0)
#define WHITE makecol(255,255,255)

//define the sprite structure
typedef struct SPRITE
{
//new elements
    int dir, alive;

    int x,y;
    int width,height;
    int xspeed,yspeed;
    int xdelay,ydelay;
    int xcount,ycount;
    int curframe,maxframe,animdir;
    int framecount,framedelay;
}SPRITE;

SPRITE mytanks[2];
SPRITE *tanks[2];
SPRITE mybullets[2];
SPRITE *bullets[2];

//replacement for the "score" variable in tank struct
int scores[2];

//declare some variables
int gameover = 0;

//sprite bitmaps
BITMAP *tank_bmp[2][8];
BITMAP *bullet_bmp;
BITMAP *explode_bmp;

//function prototypes
void drawtank(int num);
void erasetank(int num);
void movetank(int num);
void explode(int num, int x, int y);
void updatebullet(int num);
void fireweapon(int num);
void forward(int num);
void backward(int num);
void turnleft(int num);
void turnright(int num);
void getinput();
void setuptanks();
void score(int);
void setupscreen();

#endif

