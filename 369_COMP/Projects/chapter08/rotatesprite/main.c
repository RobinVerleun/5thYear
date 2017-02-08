////////////////////////////////////////////////////////////////
// Game Programming All In One, Third Edition
// Chapter 8 - RotateSprite
////////////////////////////////////////////////////////////////

#include <allegro.h>

#define WHITE makecol(255,255,255)

int main(void)
{
    int x, y;
    float angle = 0;
    BITMAP *tank;
    
    //initialize program
    allegro_init();
    install_keyboard();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
    textout_ex(screen,font,"Rotate: LEFT / RIGHT arrow keys",
        0,0,WHITE,0);

    //load tank sprite
    tank = load_bitmap("tank.bmp", NULL);
    
    //calculate center of screen
    x = SCREEN_W/2 - tank->w/2;
    y = SCREEN_H/2 - tank->h/2;

    //draw tank at starting location
    rotate_sprite(screen, tank, x, y, 0);

    //main loop
    while(!key[KEY_ESC])
    {
        //wait for keypress
        if (keypressed())
        {
            //left arrow rotates left
            if (key[KEY_LEFT])
            {   
                angle -= 0.1;
                if (angle < 0) angle = 256;
                rotate_sprite(screen, tank, x, y, itofix(angle));
            }
            
            //right arrow rotates right
            if (key[KEY_RIGHT])
            {
                angle += 0.1;
                if (angle > 256) angle = 0;
                rotate_sprite(screen, tank, x, y, itofix(angle));
            }

            //display angle
            textprintf_ex(screen, font, 0, 10, WHITE, 0,
                "Angle = %f", angle);
        }
    }
    allegro_exit();
    return 0;
}
END_OF_MAIN()


