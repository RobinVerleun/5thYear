/////////////////////////////////////////////////////////
// Game Programming All In One, Third Edition
// Chapter 14 - TestMappy
/////////////////////////////////////////////////////////

#include "allegro.h"
#include "mappyal.h"

#define MODE GFX_AUTODETECT_WINDOWED
#define WIDTH 640
#define HEIGHT 480
#define WHITE makecol(255,255,255)

//x, y offset in pixels 
int xoffset = 0;
int yoffset = 0;

//double buffer
BITMAP *buffer;	

int main (void)
{
    //initialize program
	allegro_init();	
	install_timer();
	install_keyboard();
    set_color_depth(16);
	set_gfx_mode(MODE, WIDTH, HEIGHT, 0, 0);

    //create the double buffer and clear it
	buffer = create_bitmap(SCREEN_W, SCREEN_H);	
	clear(buffer);

    //load the Mappy file
	if (MapLoad("map1.fmp") != 0)
    {
		allegro_message ("Can't find map1.fmp");
		return 1;
	}

    //main loop
    while (!key[KEY_ESC])
	{
        //check for keyboard input
		if (key[KEY_RIGHT]) xoffset+=4; 
		if (key[KEY_LEFT])  xoffset-=4; 
		if (key[KEY_UP])    yoffset-=4; 
		if (key[KEY_DOWN])  yoffset+=4; 

        //make sure it doesn't scroll beyond map edge
        if (xoffset < 0) xoffset = 0;

        if (xoffset > mapwidth*mapblockwidth-SCREEN_W) 
            xoffset = mapwidth*mapblockwidth-SCREEN_W;

        if (yoffset < 0) yoffset = 0;
        if (yoffset > mapheight*mapblockheight-SCREEN_H) 
            yoffset = mapheight*mapblockheight-SCREEN_H;

        //draw map with single layer
        MapDrawBG(buffer, xoffset, yoffset, 0, 0, SCREEN_W-1, SCREEN_H-1);

        //print scroll position
        textprintf_ex(buffer,font,0,0,WHITE,-1,
            "Position = %d,%d", xoffset, yoffset);
        textprintf_ex(buffer,font,200,0,WHITE,-1,
            "Map size = %d,%d, Tiles = %d,%d", mapwidth, mapheight, mapblockwidth, mapblockheight);

        //blit the double buffer
		blit (buffer, screen, 0, 0, 0, 0, SCREEN_W-1, SCREEN_H-1);

	}

    //delete double buffer
	destroy_bitmap(buffer);

    //delete the Mappy level
	MapFreeMem();

	allegro_exit();
	return 0;
}
END_OF_MAIN()
