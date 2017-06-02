/////////////////////////////////////////////////////////
// Game Programming All In One, Third Edition
// Chapter 13 - ArrayMapTest
/////////////////////////////////////////////////////////

#include "allegro.h"

//define some convenient constants
#define MODE GFX_AUTODETECT_WINDOWED
#define WIDTH 640
#define HEIGHT 480
#define STEP 8

//very important! double check these values!
#define TILEW 32
#define TILEH 32
#define COLS 20
#define MAP_ACROSS 31
#define MAP_DOWN 33

#define MAPW MAP_ACROSS * TILEW
#define MAPH MAP_DOWN * TILEH

int map[] = {
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,4,
4,4,1,2,2,2,2,2,2,37,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,4,4,
4,4,1,2,2,2,2,2,2,38,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,4,4,
4,4,1,2,2,2,2,2,2,39,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,4,4,
4,4,1,2,2,2,2,2,2,39,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,4,4,
4,4,1,2,2,2,2,2,2,3,3,3,3,3,3,27,27,29,3,3,3,3,3,3,3,3,3,3,1,4,4,
4,4,1,2,2,2,2,2,3,3,3,3,3,3,27,27,30,3,3,3,3,3,3,3,3,3,3,3,1,4,4,
4,4,1,15,35,36,36,3,3,3,3,3,3,27,27,27,29,3,3,3,3,3,3,3,3,3,3,3,1,4,4,
4,4,1,3,3,3,3,3,3,3,3,3,3,27,27,30,3,3,3,3,3,3,3,3,3,3,3,3,1,4,4,
4,4,1,3,3,3,3,3,3,3,3,3,27,27,4,3,3,3,3,3,3,3,3,3,3,3,3,3,1,4,4,
4,4,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,4,4,
4,4,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,4,4,
4,4,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,4,4,
4,4,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,4,4,
4,4,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,27,27,27,3,3,3,3,1,4,4,
4,4,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,27,27,27,3,3,3,3,1,4,4,
4,4,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,27,27,3,3,3,3,3,1,4,4,
4,4,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,4,4,
4,4,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,4,4,
4,4,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,4,4,
4,4,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,4,4,
4,4,1,3,3,3,3,27,27,27,3,3,3,3,3,3,3,3,3,3,3,3,3,3,15,35,35,36,1,4,4,
4,4,1,3,3,3,3,27,27,27,27,27,3,3,3,3,3,3,3,3,3,3,3,2,2,2,2,2,1,4,4,
4,4,1,3,3,3,27,27,27,27,27,27,3,3,3,3,3,3,3,3,3,3,2,2,2,2,2,2,1,4,4,
4,4,1,3,3,27,27,27,27,27,27,27,3,3,3,3,3,3,3,3,3,38,2,2,2,2,2,2,1,4,4,
4,4,1,3,3,27,27,27,3,3,3,3,3,3,3,3,3,3,3,3,3,39,2,2,2,2,2,2,1,4,4,
4,4,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,38,2,2,2,2,2,2,1,4,4,
4,4,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,39,2,2,2,2,2,2,1,4,4,
4,4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4
};

//temp bitmap
BITMAP *tiles;

//virtual background buffer
BITMAP *scroll;

//position variables
int x=0, y=0, n;
int tilex, tiley;

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

//main function
int main(void)
{
    //initialize allegro
    allegro_init();
    install_keyboard();
    install_timer();
    srand(time(NULL));
    set_color_depth(16);

    //set video mode
    set_gfx_mode(MODE, WIDTH, HEIGHT, 0, 0);

    //create the virtual background
    scroll = create_bitmap(MAPW, MAPH);

    //load the tile bitmap 
    tiles = load_bitmap("maptiles.bmp", NULL);

    //now draw tiles on virtual background
    for (tiley=0; tiley < scroll->h; tiley+=TILEH)
    {
        for (tilex=0; tilex < scroll->w; tilex+=TILEW)
        {
            //draw the tile
            drawframe(tiles, scroll, tilex, tiley, TILEW, TILEH,
                0, 0, COLS, map[n++]);
        }
    }

    //main loop
    while (!key[KEY_ESC])
    {
        //check right arrow
        if (key[KEY_RIGHT])
        {
            x += STEP;
            if (x > scroll->w - WIDTH)
                x = scroll->w - WIDTH;
        }

        //check left arrow
        if (key[KEY_LEFT])
        {
            x -= STEP;
            if (x < 0)
                x = 0;
        }

        //check down arrow
        if (key[KEY_DOWN])
        {
            y += STEP;
            if (y > scroll->h - HEIGHT)
                y = scroll->h - HEIGHT;
        }

        //check up arrow
        if (key[KEY_UP])
        {
            y -= STEP;
            if (y < 0)
                y = 0;
        }

        //draw the scroll window portion of the virtual buffer
        blit(scroll, screen, x, y, 0, 0, WIDTH-1, HEIGHT-1);

        //display status info
        textprintf_ex(screen,font,0,0,makecol(0,0,0),-1,
            "Position = (%d,%d)", x, y);

        //slow it down
        rest(20);
    }

    destroy_bitmap(scroll);
    destroy_bitmap(tiles);
    allegro_exit();
    return 0;
}
END_OF_MAIN()
