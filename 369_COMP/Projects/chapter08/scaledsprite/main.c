////////////////////////////////////////////////////////////////
// Game Programming All In One, Third Edition
// Chapter 8 - ScaledSprite
////////////////////////////////////////////////////////////////

#include <allegro.h>

#define WHITE makecol(255,255,255)

int main()
{
    BITMAP *cowboy;
	int y, n;
    float size = 8;

    //initialize the program
    allegro_init();
	install_keyboard();
	set_color_depth(16);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);

    //print some status information
    textprintf_ex(screen,font,0,0,WHITE,0,
        "Resolution = %ix%i", SCREEN_W, SCREEN_H);
    textprintf_ex(screen,font,0,10,WHITE,0,
        "Color depth = %i", bitmap_color_depth(screen));

    //load the dragon bitmap
	cowboy = load_bitmap("spacecowboy1.bmp", NULL);

    //draw the sprite
    for (n = 0; n < 11; n++)
    {
        y = 30 + size;
        stretch_sprite(screen, cowboy, size, y, size, size);
        textprintf_ex(screen,font,size+size+10,y,WHITE,0,
            "%ix%i",(int)size,(int)size);
        size *= 1.4;
    }

    //delete the bitmap
    destroy_bitmap(cowboy);

    while(!keypressed());
    allegro_exit();
    return 0;
}
END_OF_MAIN();


