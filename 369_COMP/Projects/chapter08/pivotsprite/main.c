////////////////////////////////////////////////////////////////
// Game Programming All In One, Third Edition
// Chapter 8 - PivotSprite
////////////////////////////////////////////////////////////////

#include <allegro.h>

#define WHITE makecol(255,255,255)
#define BLUE makecol(64,64,255)

int main(void)
{
    int x, y;
    int pivotx, pivoty;
    float angle = 0;
    BITMAP *tank;
    
    //initialize program
    allegro_init();
    install_keyboard();
    set_color_depth(16);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);

    //load tank sprite
    tank = load_bitmap("tank.bmp", NULL);
    
    //calculate center of screen
    x = SCREEN_W/2;
    y = SCREEN_H/2;
    pivotx = tank->w/2;
    pivoty = tank->h/2;

    //main loop
    while(!key[KEY_ESC])
    {
        //wait for keypress
        if (keypressed())
        {
            //left arrow moves pivot left
            if (key[KEY_LEFT])
            {
                pivotx -= 2;
                if (pivotx < 0)
                    pivotx = 0;
            }
            
            //right arrow moves pivot right
            if (key[KEY_RIGHT])
            {
                pivotx += 2;
                if (pivotx > tank->w-1)
                    pivotx = tank->w-1;
            }
            
            //up arrow moves pivot up
            if (key[KEY_UP])
            {
                pivoty -= 2;
                if (pivoty < 0)
                    pivoty = 0;
            }
            
            //down arrow moves pivot down
            if (key[KEY_DOWN])
            {
                pivoty += 2;
                if (pivoty > tank->h-1)
                    pivoty = tank->h-1;
            }
        }
        
        //pivot/rotate the sprite
        angle += 0.5;
        if (angle > 256) angle = 0;
        pivot_sprite(screen, tank, x, y, pivotx, pivoty, 
            itofix(angle));
        
        //draw the pivot lines
        hline(screen, 0, y, SCREEN_W-1, BLUE);
        vline(screen, x, 0, SCREEN_H-1, BLUE);
    
        //display information
        textout_ex(screen, font, 
            "Pivot Location: LEFT / RIGHT arrow keys",0,0,WHITE,0);
        textprintf_ex(screen, font, 0, 10, WHITE, 0, 
            "Pivot = %3d,%3d ", pivotx, pivoty);
        rest(1);
    }
    allegro_exit();
    return 0;
}
END_OF_MAIN()


