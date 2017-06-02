/////////////////////////////////////////////////////////////////////////
// Game Programming All In One, Third Edition
// Tank War Enhancement 7 - main.c
/////////////////////////////////////////////////////////////////////////

#include "tankwar.h"

//perform basic collision detection
int inside(int x,int y,int left,int top,int right,int bottom)
{
    if (x > left && x < right && y > top && y < bottom)
        return 1;
    else
        return 0;
}

//reuse our friendly tile grabber from chapter 9
BITMAP *grabframe(BITMAP *source, 
                  int width, int height, 
                  int startx, int starty, 
                  int columns, int frame)
{
    BITMAP *temp = create_bitmap(width,height);
    int x = startx + (frame % columns) * width;
    int y = starty + (frame / columns) * height;
    blit(source,temp,x,y,0,0,width,height);
    return temp;
}

//main function
void main(void)
{
    int anim;

    //initialize the game
    allegro_init(); 
    install_keyboard(); 
    install_timer();
    srand(time(NULL));
    setupscreen();
    setuptanks();
    loadsprites();


    //load the Mappy file
    if (MapLoad("map3.fmp") != 0)
    {
        allegro_message ("Can't find map3.fmp");
        return;
    }

    //game loop
    while(!gameover)
    {
        //move the tanks and bullets
        for (n=0; n<2; n++)
        {
            movetank(n);
            animatetank(n);
            movebullet(n);
        }

        //draw background bitmap
        blit(back, buffer, 0, 0, 0, 0, back->w, back->h);


        //draw scrolling windows (now using Mappy)
        for (n=0; n<2; n++)
            MapDrawBG(buffer, scrollx[n], scrolly[n], 
                startx[n], starty[n], SCROLLW, SCROLLH);



        //update the radar
        rectfill(buffer,radarx+1,radary+1,radarx+99,radary+88,BLACK);
        rect(buffer,radarx,radary,radarx+100,radary+89,WHITE);

        //draw mini tanks on radar
        for (n=0; n<2; n++)
            stretch_sprite(buffer, tank_bmp[n][tanks[n]->curframe][tanks[n]->dir], 
                radarx + scrollx[n]/10 + (SCROLLW/10)/2-4,
                radary + scrolly[n]/12 + (SCROLLH/12)/2-4,
                8, 8);

        //draw player viewport on radar
        for (n=0; n<2; n++)
            rect(buffer,radarx+scrollx[n]/10, radary+scrolly[n]/12,
                radarx+scrollx[n]/10+SCROLLW/10, 
                radary+scrolly[n]/12+SCROLLH/12, GRAY);

        //display score
        for (n=0; n<2; n++)
            textprintf_ex(buffer, font, startx[n], HEIGHT-10, -1,
                BURST, "Score: %d", scores[n]);

        //draw the tanks and bullets
        for (n=0; n<2; n++)
        {
            drawtank(n);
            drawbullet(n);
        }

        //explosions come last (so they draw over tanks)
        for (n=0; n<2; n++)
            updateexplosion(n);

        //refresh the screen
        acquire_screen();
        blit(buffer, screen, 0, 0, 0, 0, WIDTH-1, HEIGHT-1);
        release_screen();

        //check for keypresses
        if (keypressed())
            getinput();

        //slow the game down
        rest(20);
    }

    //destroy bitmaps
    destroy_bitmap(explode_bmp);
    destroy_bitmap(back);
    destroy_bitmap(buffer);
    
    //free tank bitmaps
    for (anim=0; anim<8; anim++)
        for (n=0; n<8; n++)
        {
            destroy_bitmap(tank_bmp[0][anim][n]);
            destroy_bitmap(tank_bmp[1][anim][n]);
        }

    //free explosion sprites
    for (n=0; n<2; n++)
        free(explosions[n]);

    //free the MappyAL memory
    MapFreeMem();

    return;
}
END_OF_MAIN();


