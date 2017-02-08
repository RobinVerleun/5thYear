////////////////////////////////////////////////////////////////
// Game Programming All In One, Third Edition
// Chapter 9 - MultipleSprites
////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <allegro.h>

#define BLACK makecol(0,0,0)
#define WHITE makecol(255,255,255)

#define NUMSPRITES 100
#define WIDTH 640
#define HEIGHT 480
#define MODE GFX_AUTODETECT_WINDOWED

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

//variables
BITMAP *spriteimg[64];
SPRITE thesprites[NUMSPRITES];
SPRITE *sprites[NUMSPRITES];
BITMAP *back;

void erasesprite(BITMAP *dest, SPRITE *spr)
{
    //erase the sprite
    blit(back, dest, spr->x, spr->y, spr->x, spr->y, 
        spr->width, spr->height);
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

void warpsprite(SPRITE *spr)
{
    //simple screen warping behavior
    if (spr->x < 0)
    {
        spr->x = SCREEN_W - spr->width;
    }

    else if (spr->x > SCREEN_W - spr->width)
    {
        spr->x = 0;
    }

    if (spr->y < 40)
    {
        spr->y = SCREEN_H - spr->height;
    }

    else if (spr->y > SCREEN_H - spr->height)
    {
        spr->y = 40;
    }

}

BITMAP *grabframe(BITMAP *source, 
                  int width, int height, 
                  int startx, int starty, 
                  int columns, int frame)
{
    BITMAP *temp = create_bitmap(width,height);

    int x = startx + (frame % columns) * width;
    int y = starty + (frame / columns) * height;
    
    blit(source,temp,x,y,0,0,width,height);

    return temp;
}

int main(void)
{
    BITMAP *temp, *buffer;
    int n;

    //initialize
    allegro_init();
    set_color_depth(16);
    set_gfx_mode(MODE, WIDTH, HEIGHT, 0, 0);
    install_keyboard();
    install_timer();
    srand(time(NULL));
    
    //create second buffer
    buffer = create_bitmap(SCREEN_W, SCREEN_H);

    //load & draw the background
    back = load_bitmap("ngc604.bmp", NULL);
    stretch_blit(back,buffer,0,0,back->w,back->h,0,0,SCREEN_W,SCREEN_H);

    //resize background to fit the variable-size screen
    destroy_bitmap(back);
    back = create_bitmap(SCREEN_W,SCREEN_H);
    blit(buffer,back,0,0,0,0,buffer->w,buffer->h);

    textout_ex(buffer, font, "MultipleSprites Program (ESC to quit)", 
        0, 0, WHITE, 0);

    //load 64-frame tiled sprite image
    temp = load_bitmap("asteroid.bmp", NULL);
    for (n=0; n<64; n++)
    {
        spriteimg[n] = grabframe(temp,64,64,0,0,8,n);
    }
    destroy_bitmap(temp);


    //initialize the sprite
    for (n=0; n<NUMSPRITES; n++)
    {
        sprites[n] = &thesprites[n];
        sprites[n]->x = rand() % (SCREEN_W - spriteimg[0]->w);
        sprites[n]->y = rand() % (SCREEN_H - spriteimg[0]->h);
        sprites[n]->width = spriteimg[0]->w;
        sprites[n]->height = spriteimg[0]->h;
        sprites[n]->xdelay = rand() % 3 + 1;
        sprites[n]->ydelay = rand() % 3 + 1;
        sprites[n]->xcount = 0;
        sprites[n]->ycount = 0;
        sprites[n]->xspeed = rand() % 8 - 5;
        sprites[n]->yspeed = rand() % 8 - 5;
        sprites[n]->curframe = rand() % 64;
        sprites[n]->maxframe = 63;
        sprites[n]->framecount = 0;
        sprites[n]->framedelay = rand() % 5 + 1;
        sprites[n]->animdir = rand() % 3 - 1;
    }

    //game loop
    while (!key[KEY_ESC])
    {
        //erase the sprites
        for (n=0; n<NUMSPRITES; n++)
            erasesprite(buffer, sprites[n]);

        //perform standard position/frame update
        for (n=0; n<NUMSPRITES; n++)
            updatesprite(sprites[n]);

        //apply screen warping behavior
        for (n=0; n<NUMSPRITES; n++)
            warpsprite(sprites[n]);

        //draw the sprites
        for (n=0; n<NUMSPRITES; n++)
            draw_sprite(buffer, spriteimg[sprites[n]->curframe], 
                sprites[n]->x, sprites[n]->y);

        //update the screen
        acquire_screen();
        blit(buffer,screen,0,0,0,0,buffer->w,buffer->h);
        release_screen();

        rest(10);
    }

    for (n=0; n<63; n++)
        destroy_bitmap(spriteimg[n]);

    allegro_exit();
    return 0;
}
END_OF_MAIN()
