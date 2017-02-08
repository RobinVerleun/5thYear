/////////////////////////////////////////////////////////////////////////
// Game Programming All In One, Third Edition
// Chapter 8 - Tank War Header (Enhancement 3)
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

//***
#define TAN makecol(255,242,169)
#define BURST makecol(255,189,73)
#define BLACK makecol(0,0,0)
#define WHITE makecol(255,255,255)

//define tank structure
struct tagTank
{
    int x,y;
    int dir,speed;
    int score;

} tanks[2];
 
//define bullet structure
struct tagBullet
{
    int x,y;
    int alive;
    int xspd,yspd;

} bullets[2];

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

