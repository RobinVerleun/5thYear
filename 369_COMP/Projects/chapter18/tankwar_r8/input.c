/////////////////////////////////////////////////////////////////////////
// Game Programming All In One, Third Edition
// Tank War Enhancement 8 - input.c
/////////////////////////////////////////////////////////////////////////

#include "tankwar.h"

void readjoysticks()
{
    int b, n;

    if (num_joysticks)
    {
        //read the joystick
        poll_joystick();
    
        for (n=0; n<2; n++)
        {
            //left stick
            if (joy[n].stick[0].axis[0].d1)
                turnleft(n);

            //right stick
            if (joy[n].stick[0].axis[0].d2)
                turnright(n);

            //forward stick
            if (joy[n].stick[0].axis[1].d1)
                forward(n);

            //backward stick
            if (joy[n].stick[0].axis[1].d2)
                backward(n);

            //any button will do
            for (b=0; b<joy[n].num_buttons; b++)
                if (joy[n].button[b].b)
                {
                    fireweapon(n);
                    break;
                }
        }
    }        
}

void forward(int num)
{
    if (key_count[num]++ > key_delay[num])
    {
        key_count[num] = 0;

        tanks[num]->xspeed++;
        if (tanks[num]->xspeed > MAXSPEED)
            tanks[num]->xspeed = MAXSPEED;
    }
}

void backward(int num)
{
    if (key_count[num]++ > key_delay[num])
    {
        key_count[num] = 0;

        tanks[num]->xspeed--;
        if (tanks[num]->xspeed < -MAXSPEED)
            tanks[num]->xspeed = -MAXSPEED;
    }
}

void turnleft(int num)
{
    if (key_count[num]++ > key_delay[num])
    {
        key_count[num] = 0;

        tanks[num]->dir--;
        if (tanks[num]->dir < 0)
            tanks[num]->dir = 7;
    }
}

void turnright(int num)
{
    if (key_count[num]++ > key_delay[num])
    {
        key_count[num] = 0;

        tanks[num]->dir++;
        if (tanks[num]->dir > 7)
            tanks[num]->dir = 0;
    }
}

void getinput()
{
    //hit ESC to quit
    if (key[KEY_ESC])   gameover = 1;

    //WASD - SPACE keys control tank 1
    if (key[KEY_W])     forward(0);
    if (key[KEY_D])     turnright(0);
    if (key[KEY_A])     turnleft(0);
    if (key[KEY_S])     backward(0);
    if (key[KEY_SPACE]) fireweapon(0);

    //arrow - ENTER keys control tank 2
    if (key[KEY_UP])    forward(1);
    if (key[KEY_RIGHT]) turnright(1);
    if (key[KEY_DOWN])  backward(1);
    if (key[KEY_LEFT])  turnleft(1);
    if (key[KEY_ENTER]) fireweapon(1);

    //short delay after keypress
    //rest(20);

}

