////////////////////////////////////////////////////////////////
// Game Programming All In One, Third Edition
// Chapter 8 - DrawSprite
////////////////////////////////////////////////////////////////

#include <allegro.h>

#define WHITE makecol(255,255,255)

int main()
{
    BITMAP *dragon;
	int x, y;

    //initialize the program
    allegro_init();
	install_keyboard();
	set_color_depth(16);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);

    //print some status information
    textprintf_ex(screen,font,0,0,WHITE,0,"Resolution = %ix%i", 
        SCREEN_W, SCREEN_H);
    textprintf_ex(screen, font, 0, 10, WHITE,0,"Color depth = %i", 
        bitmap_color_depth(screen));

    //load the dragon bitmap
	dragon = load_bitmap("spacedragon1.bmp", NULL);
    x = SCREEN_W/2 - dragon->w/2;
    y = SCREEN_H/2 - dragon->h/2;

	//main loop
    while (!key[KEY_ESC])
	{
        //erase the sprite
        rectfill(screen, x, y, x+dragon->w, y+dragon->h, 0);

        //move the sprite
        if (x-- < 2)
            x = SCREEN_W - dragon->w;

        //draw the sprite
	    draw_sprite(screen, dragon, x, y);
        
        textprintf_ex(screen,font,0,20,WHITE,0,
            "Location = %ix%i", x, y);
		rest(100000000);
	}

    //delete the bitmap
    destroy_bitmap(dragon);
    allegro_exit();
    return 0;
}
END_OF_MAIN()
