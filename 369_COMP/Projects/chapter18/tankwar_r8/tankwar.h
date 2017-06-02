//////////////////////////////////////////////////////////////////
// Game Programming All In One, Third Edition
// Tank War Enhancement 8 - tankwar.h
//////////////////////////////////////////////////////////////////

#ifndef _TANKWAR_H
#define _TANKWAR_H

#include <stdlib.h>
#include "allegro.h"
#include "mappyal.h"
#include "datafile.h"

//define the datafile object
DATAFILE *datafile;

//define some game constants
#define MODE GFX_AUTODETECT_WINDOWED
#define WIDTH 640
#define HEIGHT 480
#define MAXSPEED 4
#define BULLETSPEED 10
#define TILEW 32
#define TILEH 32
#define TILES 39
#define COLS 10
#define MAP_ACROSS 31
#define MAP_DOWN 33
#define MAPW MAP_ACROSS * TILEW
#define MAPH MAP_DOWN * TILEH
#define SCROLLW 310
#define SCROLLH 375

//define some colors
#define TAN makecol(255,242,169)
#define BURST makecol(255,189,73)
#define BLACK makecol(0,0,0)
#define WHITE makecol(255,255,255)
#define GRAY makecol(128,128,128)
#define GREEN makecol(0,255,0)

//define the sprite structure
typedef struct SPRITE
{
    int dir, alive;
    int x,y;
    int width,height;
    int xspeed,yspeed;
    int xdelay,ydelay;
    int xcount,ycount;
    int curframe,maxframe,animdir;
    int framecount,framedelay;
}SPRITE;

//sprites used in the game
SPRITE mytanks[2];
SPRITE *tanks[2];
SPRITE mybullets[2];
SPRITE *bullets[2];
SPRITE *explosions[2];


//declare some variables
int gameover;
int scores[2];
int scrollx[2], scrolly[2];
int startx[2], starty[2];
int tilex, tiley, n;
int radarx, radary;

//sprite bitmaps
BITMAP *tank_bmp[2][8][8];
BITMAP *bullet_bmp;
BITMAP *explode_bmp;

//double buffer
BITMAP *buffer;

//screen background
BITMAP *back;

//variables used for sound effects
#define PAN 128
#define PITCH 1000
#define VOLUME 128
#define NUM_SOUNDS 8
#define AMMO 0
#define HIT1 1
#define HIT2 2
#define FIRE 3
#define GOOPY 4
#define HARP 5
#define SCREAM 6
#define OHHH 7
SAMPLE *sounds[NUM_SOUNDS];

//some variables used to slow down keyboard input
int key_count[2];
int key_delay[2];


//function prototypes
void loadsounds();
void readjoysticks();
void loaddatafile();
void animatetank(int num);
void updateexplosion(int num);
void loadsprites();
void drawtank(int num);
void erasetank(int num);
void movetank(int num);
void explode(int num, int x, int y);
void movebullet(int num);
void drawbullet(int num);
void fireweapon(int num);
void forward(int num);
void backward(int num);
void turnleft(int num);
void turnright(int num);
void getinput();
void setuptanks();
void setupscreen();
int inside(int,int,int,int,int,int);
BITMAP *grabframe(BITMAP *, int, int, int, int, int, int);

#endif

