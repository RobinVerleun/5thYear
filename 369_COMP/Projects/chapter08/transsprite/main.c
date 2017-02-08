////////////////////////////////////////////////////////////////
// Game Programming All In One, Third Edition
// Chapter 8 - TransSprite
////////////////////////////////////////////////////////////////

#include <allegro.h>

int main()
{
    int x, y, c, a;
    BITMAP *background;
    BITMAP *alpha;
    BITMAP *sprite;
    BITMAP *buffer;

    //initialize
    allegro_init(); 
    install_keyboard();
    install_mouse();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);

    //load the background bitmap
    background = load_bitmap("mustang.bmp", NULL);

    //load the translucent foreground image
    alpha = load_bitmap("alpha.bmp", NULL);
    sprite = create_bitmap(alpha->w, alpha->h);

    //set the alpha channel blend values
    drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
    set_write_alpha_blender();
    //blend the two bitmap alpha channels
    for (y=0; y<alpha->h; y++) {
        for (x=0; x<alpha->w; x++) {
            //grab the pixel color
            c = getpixel(alpha, x, y);
            a = getr(c) + getg(c) + getb(c);
            //find the middle alpha value
            a = MID(0, a/2-128, 255);
            //copy the alpha-enabled pixel to the sprite
            putpixel(sprite, x, y, a);
        }
    }

    //create a double buffer bitmap
    buffer = create_bitmap(SCREEN_W, SCREEN_H);

    //draw the background image
    blit(background, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

    while (!key[KEY_ESC])
    {
        //get the mouse coordinates
        x = mouse_x - sprite->w/2;
        y = mouse_y - sprite->h/2;

        //draw the translucent image
        set_alpha_blender();
        draw_trans_sprite(buffer, sprite, x, y);

        //draw memory buffer to the screen
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        //restore the background
        blit(background, buffer, x, y, x, y, sprite->w, sprite->h);
    }
    
    destroy_bitmap(background);
    destroy_bitmap(sprite);
    destroy_bitmap(buffer);
    destroy_bitmap(alpha);

    allegro_exit();
    return 0;
}
END_OF_MAIN()
