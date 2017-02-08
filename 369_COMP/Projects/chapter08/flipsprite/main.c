////////////////////////////////////////////////////////////////
// Game Programming All In One, Third Edition
// Chapter 8 - FlipSprite
////////////////////////////////////////////////////////////////

#include <allegro.h>

int main()
{
    BITMAP *panel;

    //initialize the program
    allegro_init();
	install_keyboard();
	set_color_depth(16);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);

    //load the dragon bitmap
	panel = load_bitmap("panel.bmp", NULL);

    //draw the sprite
    draw_sprite(screen, panel, 200, 100);
    draw_sprite_h_flip(screen, panel, 200+128, 100);
    draw_sprite_v_flip(screen, panel, 200, 100+128);
    draw_sprite_vh_flip(screen, panel, 200+128, 100+128);

    //delete the bitmap
    destroy_bitmap(panel);

    while(!keypressed());
    allegro_exit();
    return 0;
}
END_OF_MAIN()
