/////////////////////////////////////////////////////////////////////////
// Game Programming All In One, Third Edition
// Chapter 4 - Tank War Game
/////////////////////////////////////////////////////////////////////////

#ifndef _TANKWAR_H
#define _TANKWAR_H

#include "allegro.h"

//define some game constants
#define MODE GFX_AUTODETECT_WINDOWED
#define WIDTH 640
#define HEIGHT 480
#define BLOCKS 5
#define BLOCKSIZE 100
#define MAXSPEED 2
#define BULLETSPEED 10
#define TAN makecol(255,242,169)
#define CAMO makecol(64,142,66)
#define BURST makecol(255,189,73)

//define tank structure
struct tagTank
{
    int x,y;
    int dir,speed;
    int color;
    int score;

} tanks[2];

//define bullet structure
struct tagBullet
{
    int x,y;
    int alive;
    int xspd,yspd;

} bullets[2];

int gameover = 0;

//function prototypes
void drawtank(int num);
void erasetank(int num);
void movetank(int num);
void explode(int num, int x, int y);
void updatebullet(int num);
int checkpath(int x1,int y1,int x2,int y2,int x3,int y3);
void clearpath(int num);
void fireweapon(int num);
void forward(int num);
void backward(int num);
void turnleft(int num);
void turnright(int num);
void getinput();
void setuptanks();
void score(int);
void print(const char *s, int c);
void setupdebris();
void setupscreen();

#endif

