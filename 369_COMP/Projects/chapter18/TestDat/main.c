//////////////////////////////////////////////////////
// Game Programming All In One, Third Edition
// Chapter 18 - TestDat
//////////////////////////////////////////////////////

#include <allegro.h>

#define MODE GFX_AUTODETECT_WINDOWED
#define WIDTH 640
#define HEIGHT 480
#define WHITE makecol(255,255,255)

//define objects in datfile
#define BACK_BMP 0
#define SHIP_BMP 1


int main(void)
{
    DATAFILE *data;
    BITMAP *sprite;

    //initialize the program
    allegro_init();
    install_keyboard(); 
    install_timer();
    set_color_depth(16);
    set_gfx_mode(MODE, WIDTH, HEIGHT, 0, 0);

    //load the datfile
    data = load_datafile("test.dat");

    //blit the background image using datfile directly
    blit(data[BACK_BMP].dat, screen, 0, 0, 0, 0, WIDTH-1, HEIGHT-1);

    //grab sprite and store in separate BITMAP
    sprite = (BITMAP *)data[SHIP_BMP].dat;
    draw_sprite(screen, sprite, WIDTH/2-sprite->w/2,HEIGHT/2-sprite->h/2);

    //display title
    textout_ex(screen,font,"TestDat Program (ESC to quit)",0,0,WHITE,-1);

    //pause
    while(!keypressed());

    //remove datfile from memory
    unload_datafile(data);

    allegro_exit();
    return 0;
}
END_OF_MAIN()
