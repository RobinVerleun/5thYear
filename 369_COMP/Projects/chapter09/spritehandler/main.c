////////////////////////////////////////////////////////////////
// Game Programming All In One, Third Edition
// Chapter 9 - SpriteHandler
////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <allegro.h>

#define BLACK makecol(0,0,0)
#define WHITE makecol(255,255,255)

//define the sprite structure
typedef struct SPRITE
{
	int x,y;
	int width,height;
	int xspeed,yspeed;
	int xdelay,ydelay;
	int xcount,ycount;
	int curframe,maxframe,animdir;
	int framecount,framedelay;
	
}SPRITE;

//sprite variables
BITMAP *ballimg[16];
SPRITE theball;
SPRITE *ball = &theball;

//support variables
char s[20];
int n;

void erasesprite(BITMAP *dest, SPRITE *spr)
{
    //erase the sprite using BLACK color fill
    rectfill(dest, spr->x, spr->y, spr->x + spr->width, 
        spr->y + spr->height, BLACK);
}

void updatesprite(SPRITE *spr)
{
    //update x position
    if (++spr->xcount > spr->xdelay)
    {
        spr->xcount = 0;
        spr->x += spr->xspeed;
    }

    //update y position
    if (++spr->ycount > spr->ydelay)
    {
        spr->ycount = 0;
        spr->y += spr->yspeed;
    }

    //update frame based on animdir
    if (++spr->framecount > spr->framedelay)
    {
        spr->framecount = 0;
        if (spr->animdir == -1)
        {
            if (--spr->curframe < 0)
                spr->curframe = spr->maxframe;
        }
        else if (spr->animdir == 1)
        {
            if (++spr->curframe > spr->maxframe)
                spr->curframe = 0;
        }
    }
}

void bouncesprite(SPRITE *spr)
{
    //simple screen bouncing behavior
    if (spr->x < 0)
    {
        spr->x = 0;
        spr->xspeed = rand() % 2 + 4;
        spr->animdir *= -1;
    }

    else if (spr->x > SCREEN_W - spr->width)
    {
        spr->x = SCREEN_W - spr->width;
        spr->xspeed = rand() % 2 - 6;
        spr->animdir *= -1;
    }

    if (spr->y < 40)
    {
        spr->y = 40;
        spr->yspeed = rand() % 2 + 4;
        spr->animdir *= -1;
    }

    else if (spr->y > SCREEN_H - spr->height)
    {
        spr->y = SCREEN_H - spr->height;
        spr->yspeed = rand() % 2 - 6;
        spr->animdir *= -1;
    }

}

int main(void)
{
    //initialize
    allegro_init();
    set_color_depth(16);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
    install_keyboard();
    install_timer();
    srand(time(NULL));
    textout_ex(screen, font, "SpriteHandler Program (ESC to quit)", 
        0, 0, WHITE, 0);
    
    //load sprite images
    for (n=0; n<16; n++)
    {
        sprintf(s,"ball%d.bmp",n+1);
        ballimg[n] = load_bitmap(s, NULL);
    }

    //initialize the sprite with lots of randomness
    ball->x = rand() % (SCREEN_W - ballimg[0]->w);
    ball->y = rand() % (SCREEN_H - ballimg[0]->h);
    ball->width = ballimg[0]->w;
    ball->height = ballimg[0]->h;
    ball->xdelay = rand() % 2 + 1;
    ball->ydelay = rand() % 2 + 1;
    ball->xcount = 0;
    ball->ycount = 0;
    ball->xspeed = rand() % 2 + 4; 
    ball->yspeed = rand() % 2 + 4;
    ball->curframe = 0;
    ball->maxframe = 15;
    ball->animdir = 1;
    ball->framecount = 0;
    ball->framedelay = rand() % 3 + 1;
    ball->animdir = 1;

    //game loop
    while (!key[KEY_ESC])
    {
        erasesprite(screen, ball);

        //perform standard position/frame update
        updatesprite(ball);

        //now do something with the sprite--a basic screen bouncer
        bouncesprite(ball);

        //lock the screen
        acquire_screen();

        //draw the ball sprite
        draw_sprite(screen, ballimg[ball->curframe], ball->x, ball->y);

        //display some logistics
        textprintf_ex(screen, font, 0, 20, WHITE, 0,
            "x,y,xspeed,yspeed: %2d,%2d,%2d,%2d",
            ball->x, ball->y, ball->xspeed, ball->yspeed);
        textprintf_ex(screen, font, 0, 30, WHITE, 0,
            "xcount,ycount,framecount,animdir: %2d,%2d,%2d,%2d",
            ball->xcount, ball->ycount, ball->framecount, ball->animdir);

        //unlock the screen
        release_screen();

        rest(10);
    }
    for (n=0; n<15; n++)
        destroy_bitmap(ballimg[n]);

    allegro_exit();
    return 0;
}
END_OF_MAIN()
