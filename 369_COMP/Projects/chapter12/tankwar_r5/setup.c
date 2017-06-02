/////////////////////////////////////////////////////////////////////////
// Game Programming All In One, Second Edition
// Source Code Copyright (C)2004 by Jonathan S. Harbour
// Tank War Enhancement 5 - setup.c
/////////////////////////////////////////////////////////////////////////

#include "tankwar.h"

void setuptanks()
{
    int n;
    
    //configure player 1's tank
    tanks[0] = &mytanks[0];
    tanks[0]->x = 30;
    tanks[0]->y = 40;
    tanks[0]->xspeed = 0;
    scores[0] = 0;
    tanks[0]->dir = 3;

    //load first tank bitmap
    tank_bmp[0][0] = load_bitmap("tank1.bmp", NULL);
    
    //rotate image to generate all 8 directions
    for (n=1; n<8; n++)
    {
        tank_bmp[0][n] = create_bitmap(32, 32);
        clear_to_color(tank_bmp[0][n], makecol(255,0,255));
        rotate_sprite(tank_bmp[0][n], tank_bmp[0][0], 
            0, 0, itofix(n*32));
    }

    //configure player 2's tank
    tanks[1] = &mytanks[1];
    tanks[1]->x = SCREEN_W-30;
    tanks[1]->y = SCREEN_H-30;
    tanks[1]->xspeed = 0;
    scores[1] = 0;
    tanks[1]->dir = 7;
    
    //load second tank bitmap
    tank_bmp[1][0] = load_bitmap("tank2.bmp", NULL);    
    
    //rotate image to generate all 8 directions
    for (n=1; n<8; n++)
    {
        tank_bmp[1][n] = create_bitmap(32, 32);
        clear_to_color(tank_bmp[1][n], makecol(255,0,255));
        rotate_sprite(tank_bmp[1][n], tank_bmp[1][0], 
            0, 0, itofix(n*32));
    }

    //load bullet image
    if (bullet_bmp == NULL)
        bullet_bmp = load_bitmap("bullet.bmp", NULL);

    //initialize bullets
    for (n=0; n<2; n++)
    {
       bullets[n] = &mybullets[n];
       bullets[n]->x = 0;
       bullets[n]->y = 0;
       bullets[n]->width = bullet_bmp->w;
       bullets[n]->height = bullet_bmp->h;
    }

    //center tanks inside scroll windows
    tanks[0]->x = 5 + SCROLLW/2;
    tanks[0]->y = 90 + SCROLLH/2;
    tanks[1]->x = 325 + SCROLLW/2;
    tanks[1]->y = 90 + SCROLLH/2;
}

void setupscreen()
{
    int ret;

    //set video mode    
    set_color_depth(16);
    ret = set_gfx_mode(MODE, WIDTH, HEIGHT, 0, 0);
    if (ret != 0) {
        allegro_message(allegro_error);
        return;
    }

    //create the virtual background
    scroll = create_bitmap(MAPW, MAPH);
    if (scroll == NULL)
    {
        set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
        allegro_message("Error creating virtual background");
        return;
    }

    //load the tile bitmap
    tiles = load_bitmap("tiles.bmp", NULL);
    if (tiles == NULL)
    {
        set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
        allegro_message("Error loading tiles.bmp file");
        return;
    }

    //now draw tiles on virtual background
    for (tiley=0; tiley < scroll->h; tiley+=TILEH)
    {
        for (tilex=0; tilex < scroll->w; tilex+=TILEW)
        {
            //use the result of grabframe directly in blitter
            blit(grabframe(tiles, TILEW+1, TILEH+1, 0, 0, COLS, map[n++]), 
                scroll, 0, 0, tilex, tiley, TILEW, TILEH);
        }
    }

    //done with tiles
    destroy_bitmap(tiles);

    //load screen background
    back = load_bitmap("background.bmp", NULL);
    if (back == NULL)
    {
        set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
        allegro_message("Error loading background.bmp file");
        return;
    }

    //create the double buffer
    buffer = create_bitmap(WIDTH, HEIGHT);
    if (buffer == NULL)
    {
        set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
        allegro_message("Error creating double buffer");
        return;
    }

    //position the radar
    radarx = 270;
    radary = 1;

    //position each player
    scrollx[0] = 100;
    scrolly[0] = 100;
    scrollx[1] = MAPW - 400;
    scrolly[1] = MAPH - 500;

    //position the scroll windows
    startx[0] = 5;
    starty[0] = 93;
    startx[1] = 325;
    starty[1] = 93;

}

