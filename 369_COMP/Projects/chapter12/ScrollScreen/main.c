//////////////////////////////////////////////////
// Game Programming All In One, Third Edition
// Chapter 12 - ScrollScreen
//////////////////////////////////////////////////

#include "allegro.h"

//define some convenient constants
#define MODE GFX_AUTODETECT_WINDOWED
#define WIDTH 640
#define HEIGHT 480
#define STEP 8

//virtual buffer variable
BITMAP *scroll;

//position variables
int x=0, y=0;

//main function
int main(void)
{
    //initialize allegro
    allegro_init();
    install_keyboard();
    install_timer();
    set_color_depth(16);
    set_gfx_mode(MODE, WIDTH, HEIGHT, 0, 0);

    //load the large bitmap image from disk
    scroll = load_bitmap("bigbg.bmp", NULL);

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

        //slow it down
        rest(20);
    }

    allegro_exit();
    return 0;
}
END_OF_MAIN()
