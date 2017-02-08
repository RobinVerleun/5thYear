////////////////////////////////////////////////////////////////
// Game Programming All In One, Third Edition
// Chapter 9 - DrawFrame
////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <allegro.h>

#define MODE GFX_AUTODETECT_WINDOWED
#define WIDTH 800
#define HEIGHT 600
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
        spr->xspeed = rand() % 2 + 2;
        spr->animdir *= -1;
    }

    else if (spr->x > SCREEN_W - spr->width)
    {
        spr->x = SCREEN_W - spr->width;
        spr->xspeed = rand() % 2 - 4;
        spr->animdir *= -1;
    }

    if (spr->y < 0)
    {
        spr->y = 0;
        spr->yspeed = rand() % 2 + 2;
        spr->animdir *= -1;
    }

    else if (spr->y > SCREEN_H - spr->height)
    {
        spr->y = SCREEN_H - spr->height;
        spr->yspeed = rand() % 2 - 4;
        spr->animdir *= -1;
    }

}

void drawframe(BITMAP *source, BITMAP *dest, 
               int x, int y, int width, int height, 
               int startx, int starty, int columns, int frame)
{
    //calculate frame position
    int framex = startx + (frame % columns) * width;
    int framey = starty + (frame / columns) * height;
    //draw frame to destination bitmap
    masked_blit(source,dest,framex,framey,x,y,width,height);
}

int main(void)
{
	//images and sprites
	BITMAP *buffer;
	BITMAP *bg;
	SPRITE theball;
	SPRITE *ball = &theball;
	BITMAP *ballimage;

    //initialize
    allegro_init();
    set_color_depth(16);
    set_gfx_mode(MODE, WIDTH, HEIGHT, 0, 0);
    install_keyboard();
    install_timer();
    srand(time(NULL));

	//create the back buffer
	buffer = create_bitmap(WIDTH,HEIGHT);

	//load background
	bg = load_bitmap("bluespace.bmp", NULL);
	if (!bg) {
		allegro_message("Error loading background image\n%s", allegro_error);
		return 1;
	}
    
    //load 32-frame tiled sprite image
    ballimage = load_bitmap("sphere.bmp", NULL);
	if (!ballimage) {
		allegro_message("Error loading ball image\n%s", allegro_error);
		return 1;
	}

    //randomize the sprite
    ball->x = SCREEN_W / 2;
    ball->y = SCREEN_H / 2;
    ball->width = 64;
    ball->height = 64;
    ball->xdelay = rand() % 2 + 1;
    ball->ydelay = rand() % 2 + 1;
    ball->xcount = 0;
    ball->ycount = 0;
    ball->xspeed = rand() % 2 + 2;
    ball->yspeed = rand() % 2 + 2;
    ball->curframe = 0;
    ball->maxframe = 31;
    ball->framecount = 0;
    ball->framedelay = 1;
    ball->animdir = 1;

    //game loop
    while (!key[KEY_ESC])
    {
	    //fill screen with background image
		blit(bg, buffer, 0, 0, 0, 0, WIDTH, HEIGHT);

        //update the sprite
        updatesprite(ball);
        bouncesprite(ball);
		drawframe(ballimage, buffer, ball->x, ball->y, 64, 64, 0, 0, 8, ball->curframe);

        //display some info
		textout_ex(buffer, font, "DrawFrame Program (ESC to quit)", 
            0, 0, WHITE, 0);
        textprintf_ex(buffer, font, 0, 20, WHITE, 0, 
            "Position: %2d,%2d", ball->x, ball->y);

        //refresh the screen
        acquire_screen();
		blit(buffer, screen, 0, 0, 0, 0, WIDTH, HEIGHT);
        release_screen();
        rest(10);
    }

	destroy_bitmap(ballimage);
	destroy_bitmap(bg);
	destroy_bitmap(buffer);
	allegro_exit();
    return 0;
}
END_OF_MAIN()
