//////////////////////////////////////////////////////
// Game Programming All In One, Third Edition
// Chapter 21 - MultiThread
//////////////////////////////////////////////////////

#include <pthread.h>
#include "allegro.h"
#include <stdio.h>

#define MODE GFX_AUTODETECT_WINDOWED
#define WIDTH 640
#define HEIGHT 480
#define BLACK makecol(0,0,0)
#define WHITE makecol(255,255,255)

//define the sprite structure
typedef struct SPRITE
{
    int dir, alive;
    int x,y;
    int width,height;
    int xspeed,yspeed;
    int xdelay,ydelay;
    int xcount,ycount;
    int curframe,maxframe,animdir;
    int framecount,framedelay;
}SPRITE;

//variables
BITMAP *buffer;
BITMAP *ballimg[32];
SPRITE theballs[2];
SPRITE *balls[2];
int done;
int n;

//create a new thread mutex to protect variables
pthread_mutex_t threadsafe = PTHREAD_MUTEX_INITIALIZER;


void erasesprite(BITMAP *dest, SPRITE *spr)
{
    //erase the sprite
    rectfill(dest, spr->x, spr->y, spr->x + spr->width, 
        spr->y + spr->height, BLACK);
}

void updatesprite(SPRITE *spr)
{
    //update x position
    if (++spr->xcount > spr->xdelay)
    {
        spr->xcount = 0;
        spr->x += spr->xspeed;
    }

    //update y position
    if (++spr->ycount > spr->ydelay)
    {
        spr->ycount = 0;
        spr->y += spr->yspeed;
    }

    //update frame based on animdir
    if (++spr->framecount > spr->framedelay)
    {
        spr->framecount = 0;
        if (spr->animdir == -1)
        {
            if (--spr->curframe < 0)
                spr->curframe = spr->maxframe;
        }
        else if (spr->animdir == 1)
        {
            if (++spr->curframe > spr->maxframe)
                spr->curframe = 0;
        }
    }
}

//this version doesn't change speed, just direction
void bouncesprite(SPRITE *spr)
{
    //simple screen bouncing behavior
    if (spr->x < 0)
    {
        spr->x = 0;
        spr->xspeed = -spr->xspeed;
        spr->animdir *= -1;
    }

    else if (spr->x > SCREEN_W - spr->width)
    {
        spr->x = SCREEN_W - spr->width;
        spr->xspeed = -spr->xspeed;
        spr->animdir *= -1;
    }

    if (spr->y < 0)
    {
        spr->y = 0;
        spr->yspeed = -spr->yspeed;
        spr->animdir *= -1;
    }

    else if (spr->y > SCREEN_H - spr->height)
    {
        spr->y = SCREEN_H - spr->height;
        spr->yspeed = -spr->yspeed;
        spr->animdir *= -1;
    }
}

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

void loadsprites()
{
    BITMAP *temp;

    //load sprite images
    temp = load_bitmap("sphere.bmp", NULL);
    for (n=0; n<32; n++)
        ballimg[n] = grabframe(temp,64,64,0,0,8,n);
    destroy_bitmap(temp);

    //initialize the sprite
    for (n=0; n<2; n++)
    {
        balls[n] = &theballs[n];
        balls[n]->x = rand() % (SCREEN_W - ballimg[0]->w);
        balls[n]->y = rand() % (SCREEN_H - ballimg[0]->h);
        balls[n]->width = ballimg[0]->w;
        balls[n]->height = ballimg[0]->h;
        balls[n]->xdelay = 0;
        balls[n]->ydelay = 0;
        balls[n]->xcount = 0;
        balls[n]->ycount = 0;
        balls[n]->xspeed = 5;
        balls[n]->yspeed = 5;
        balls[n]->curframe = rand() % 32;
        balls[n]->maxframe = 31;
        balls[n]->framecount = 0;
        balls[n]->framedelay = 0;
        balls[n]->animdir = 1;
    }
}

//this thread updates sprite 0
void* thread0(void* data)
{
    //get this thread id
    int my_thread_id = *((int*)data);

    //thread's main loop
    while(!done)
    {
        //lock the mutex to protect variables
        if (pthread_mutex_lock(&threadsafe))
            textout_ex(buffer,font,"ERROR: thread mutex was locked",0,0,WHITE,0);
        
        //erase sprite 0
        erasesprite(buffer, balls[0]);

        //update sprite 0
        updatesprite(balls[0]);

        //bounce sprite 0
        bouncesprite(balls[0]);

        //draw sprite 0
        draw_sprite(buffer, ballimg[balls[0]->curframe], 
            balls[0]->x, balls[0]->y);

        //print sprite number
        textout_ex(buffer, font, "0", balls[0]->x, balls[0]->y,WHITE,0);

        //display sprite position
        textprintf_ex(buffer,font,0,10,WHITE,0,"THREAD ID %d, SPRITE (%3d,%3d)",
            my_thread_id, balls[0]->x, balls[0]->y);

        //unlock the mutex
        if (pthread_mutex_unlock(&threadsafe))
            textout_ex(buffer,font,"ERROR: thread mutex unlock error",0,0,WHITE,0);

        //slow down (this thread only!)
    	rest(10);
    }

    // terminate the thread
    pthread_exit(NULL);

    return NULL;
}

//this thread updates sprite 1
void* thread1(void* data)
{
    //get this thread id
    int my_thread_id = *((int*)data);

    //thread's main loop
    while(!done)
    {
        //lock the mutex to protect variables
        if (pthread_mutex_lock(&threadsafe))
            textout_ex(buffer,font,"ERROR: thread mutex was locked",0,0,WHITE,0);

        //erase sprite 1
        erasesprite(buffer, balls[1]);

        //update sprite 1
        updatesprite(balls[1]);

        //bounce sprite 1
        bouncesprite(balls[1]);

        //draw sprite 1
        draw_sprite(buffer, ballimg[balls[1]->curframe], 
            balls[1]->x, balls[1]->y);

        //print sprite number
        textout_ex(buffer, font, "1", balls[1]->x, balls[1]->y,WHITE,0);

        //display sprite position
        textprintf_ex(buffer,font,0,20,WHITE,0,"THREAD ID %d, SPRITE (%3d,%3d)",
            my_thread_id, balls[1]->x, balls[1]->y);

        //unlock the mutex
        if (pthread_mutex_unlock(&threadsafe))
            textout_ex(buffer,font,"ERROR: thread mutex unlock error",0,0,WHITE,0);

        //slow down (this thread only!)
    	rest(20);
    }

    // terminate the thread
    pthread_exit(NULL);

    return NULL;
}

//program's primary thread
void main(void)
{
    int id;
    pthread_t pthread0;
    pthread_t pthread1;
    int threadid0 = 0;
    int threadid1 = 1;

    //initialize
    allegro_init();
    set_color_depth(16);
    set_gfx_mode(MODE, WIDTH, HEIGHT, 0, 0);
    srand(time(NULL));
    install_keyboard();
    install_timer();

    //create double buffer
    buffer = create_bitmap(SCREEN_W,SCREEN_H);

    //load ball sprite 
    loadsprites();

    //create the thread for sprite 0
    id = pthread_create(&pthread0, NULL, thread0, (void*)&threadid0);

    //create the thread for sprite 1
    id = pthread_create(&pthread1, NULL, thread1, (void*)&threadid1);

    //main loop
    while (!key[KEY_ESC])
    {
        //lock the mutex to protect double buffer
        pthread_mutex_lock(&threadsafe);
        printf("Here\n");

        //display title
        textout_ex(buffer, font, "MultiThread Program (ESC to quit)", 0, 0, WHITE,0);

        //update the screen
        acquire_screen();
        blit(buffer,screen,0,0,0,0,SCREEN_W-1,SCREEN_H-1);
        release_screen();

        //unlock the mutex
        pthread_mutex_unlock(&threadsafe);

        //note there is no delay
    }

    //tell threads it's time to quit
    done++;
    rest(100);

    //kill the mutex (thread protection)
    pthread_mutex_destroy(&threadsafe);
    
    //remove objects from memory
    destroy_bitmap(buffer);

    //delete sprites
    for (n=0; n<32; n++)
        destroy_bitmap(ballimg[n]);

    return;
}

END_OF_MAIN();



