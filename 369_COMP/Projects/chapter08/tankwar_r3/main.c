/////////////////////////////////////////////////////////////////////
// Game Programming All In One, Third Edition
// Chapter 8 - Tank War Game (Enhancement 3)
/////////////////////////////////////////////////////////////////////

#include "tankwar.h"

/////////////////////////////////////////////////////////////////////
// drawtank function
// display the tank bitmap in the current direction
/////////////////////////////////////////////////////////////////////
void drawtank(int num)
{
    int dir = tanks[num].dir;
    int x = tanks[num].x-15;
    int y = tanks[num].y-15;
    draw_sprite(screen, tank_bmp[num][dir], x, y);
}

/////////////////////////////////////////////////////////////////////
// erasetank function
// erase the tank using rectfill
/////////////////////////////////////////////////////////////////////
void erasetank(int num)
{
    int x = tanks[num].x-17;
    int y = tanks[num].y-17;
    rectfill(screen, x, y, x+33, y+33, BLACK);
}

/////////////////////////////////////////////////////////////////////
// movetank function
// move the tank in the current direction
/////////////////////////////////////////////////////////////////////
void movetank(int num){
    int dir = tanks[num].dir;
    int speed = tanks[num].speed;

    //update tank position based on direction
    switch(dir)
    {
        case 0:
            tanks[num].y -= speed;
            break;
        case 1:
            tanks[num].x += speed;
            tanks[num].y -= speed;
            break;
        case 2:
            tanks[num].x += speed;
            break;
        case 3:
            tanks[num].x += speed;
            tanks[num].y += speed;
            break;
        case 4:
            tanks[num].y += speed;
            break;
        case 5:
            tanks[num].x -= speed;
            tanks[num].y += speed;
            break;
        case 6:
            tanks[num].x -= speed;
            break;
        case 7:
            tanks[num].x -= speed;
            tanks[num].y -= speed;
            break;
    }

    //keep tank inside the screen
    if (tanks[num].x > SCREEN_W-22)
    {
        tanks[num].x = SCREEN_W-22;
        tanks[num].speed = 0;
    }
    if (tanks[num].x < 22)
    {
        tanks[num].x = 22;
        tanks[num].speed = 0;
    }
    if (tanks[num].y > SCREEN_H-22)
    {
        tanks[num].y = SCREEN_H-22;
        tanks[num].speed = 0;
    }
    if (tanks[num].y < 22)
    {
        tanks[num].y = 22;
        tanks[num].speed = 0;
    }
}

/////////////////////////////////////////////////////////////////////
// explode function
// display an explosion image
/////////////////////////////////////////////////////////////////////
void explode(int num, int x, int y)
{
    int n;

    //load explode image
    if (explode_bmp == NULL)
    {
        explode_bmp = load_bitmap("explode.bmp", NULL);
    }
    
    //draw the explosion bitmap several times
    for (n = 0; n < 5; n++)
    {
        rotate_sprite(screen, explode_bmp, 
            x + rand()%10 - 20, y + rand()%10 - 20, 
            itofix(rand()%255));

        rest(30);
    }

    //clear the explosion
    circlefill(screen, x, y, 50, BLACK);
   
}

/////////////////////////////////////////////////////////////////////
// updatebullet function
// update the position of a bullet
/////////////////////////////////////////////////////////////////////
void updatebullet(int num)
{
    int x = bullets[num].x;
    int y = bullets[num].y;
    int tx, ty;

    //is the bullet active?
    if (!bullets[num].alive) return;
    
    //erase bullet
    rectfill(screen, x, y, x+10, y+10, BLACK);        

    //move bullet
    bullets[num].x += bullets[num].xspd;
    bullets[num].y += bullets[num].yspd;
    x = bullets[num].x;
    y = bullets[num].y;

    //stay within the screen
    if (x < 6 || x > SCREEN_W-6 || y < 20 || y > SCREEN_H-6)
    {
        bullets[num].alive = 0;
        return;
    }

    //look for a direct hit using basic collision
    //tank is either 0 or 1, so negative num = other tank
    tx = tanks[!num].x;
    ty = tanks[!num].y;
    if (x > tx-16 && x < tx+16 && y > ty-16 && y < ty+16)
    {
        //kill the bullet
        bullets[num].alive = 0;
            
        //blow up the tank
        explode(num, x, y);
        score(num);
    }
    else
    //if no hit then draw the bullet
    {
        //draw bullet sprite
        draw_sprite(screen, bullet_bmp, x, y);

        //update the bullet positions (for debugging)
        textprintf_ex(screen, font, SCREEN_W/2-50, 1, TAN, 0,
            "B1 %-3dx%-3d  B2 %-3dx%-3d", 
            bullets[0].x, bullets[0].y, 
            bullets[1].x, bullets[1].y);
    }
}


/////////////////////////////////////////////////////////////////////
// fireweapon function
// set bullet direction and speed and activate it
/////////////////////////////////////////////////////////////////////
void fireweapon(int num)
{
    int x = tanks[num].x;
    int y = tanks[num].y;

    //load bullet image if necessary
    if (bullet_bmp == NULL)
    {
        bullet_bmp = load_bitmap("bullet.bmp", NULL);
    }

    //ready to fire again?
    if (!bullets[num].alive)
    {
        bullets[num].alive = 1;

        //fire bullet in direction tank is facing
        switch (tanks[num].dir)
        {
            //north
            case 0:
                bullets[num].x = x-2;
                bullets[num].y = y-22;
                bullets[num].xspd = 0;
                bullets[num].yspd = -BULLETSPEED;
                break;
            //NE
            case 1:
                bullets[num].x = x+18;
                bullets[num].y = y-18;
                bullets[num].xspd = BULLETSPEED;
                bullets[num].yspd = -BULLETSPEED;         
                break;  
            //east
            case 2:
                bullets[num].x = x+22;
                bullets[num].y = y-2;
                bullets[num].xspd = BULLETSPEED;
                bullets[num].yspd = 0;
                break;
            //SE
            case 3:
                bullets[num].x = x+18;
                bullets[num].y = y+18;
                bullets[num].xspd = BULLETSPEED;
                bullets[num].yspd = BULLETSPEED;
                break;
            //south
            case 4:
                bullets[num].x = x-2;
                bullets[num].y = y+22;
                bullets[num].xspd = 0;
                bullets[num].yspd = BULLETSPEED;
                break;
            //SW
            case 5:
                bullets[num].x = x-18;
                bullets[num].y = y+18;
                bullets[num].xspd = -BULLETSPEED;
                bullets[num].yspd = BULLETSPEED;
                break;
            //west
            case 6:
                bullets[num].x = x-22;
                bullets[num].y = y-2;
                bullets[num].xspd = -BULLETSPEED;
                bullets[num].yspd = 0;
                break;
            //NW
            case 7:
                bullets[num].x = x-18;
                bullets[num].y = y-18;
                bullets[num].xspd = -BULLETSPEED;
                bullets[num].yspd = -BULLETSPEED;
                break;
        }
    }
}

/////////////////////////////////////////////////////////////////////
// forward function
// increase the tank's speed
/////////////////////////////////////////////////////////////////////
void forward(int num)
{
    tanks[num].speed++;
    if (tanks[num].speed > MAXSPEED)
        tanks[num].speed = MAXSPEED;
}

/////////////////////////////////////////////////////////////////////
// backward function
// decrease the tank's speed
/////////////////////////////////////////////////////////////////////
void backward(int num)
{
    tanks[num].speed--;
    if (tanks[num].speed < -MAXSPEED)
        tanks[num].speed = -MAXSPEED;
}

/////////////////////////////////////////////////////////////////////
// turnleft function
// rotate the tank counter-clockwise
/////////////////////////////////////////////////////////////////////
void turnleft(int num)
{
    tanks[num].dir--;
    if (tanks[num].dir < 0)
        tanks[num].dir = 7;
}

/////////////////////////////////////////////////////////////////////
// turnright function
// rotate the tank clockwise
/////////////////////////////////////////////////////////////////////
void turnright(int num)
{
    tanks[num].dir++;
    if (tanks[num].dir > 7)
        tanks[num].dir = 0;
}

/////////////////////////////////////////////////////////////////////
// getinput function
// check for player input keys (2 player support)
/////////////////////////////////////////////////////////////////////
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
    rest(20);
}

/////////////////////////////////////////////////////////////////////
// score function
// add a point to a player's score
/////////////////////////////////////////////////////////////////////
void score(int player)
{
    //update score
    int points = ++tanks[player].score;

    //display score
    textprintf_ex(screen, font, SCREEN_W-70*(player+1), 1, 0,
        BURST, "P%d: %d", player+1, points);
}

/////////////////////////////////////////////////////////////////////
// setuptanks function
// load tank bitmaps and position the tank
/////////////////////////////////////////////////////////////////////
void setuptanks()
{
    int n;
    
    //configure player 1's tank
    tanks[0].x = 30;
    tanks[0].y = 40;
    tanks[0].speed = 0;
    tanks[0].score = 0;
    tanks[0].dir = 3;

    //load first tank bitmap
    tank_bmp[0][0] = load_bitmap("tank1.bmp", NULL);
    
    //rotate image to generate all 8 directions
    for (n=1; n<8; n++)
    {
        tank_bmp[0][n] = create_bitmap(32, 32);
        clear_bitmap(tank_bmp[0][n]);
        rotate_sprite(tank_bmp[0][n], tank_bmp[0][0], 
            0, 0, itofix(n*32));
    }

    //configure player 2's tank
    tanks[1].x = SCREEN_W-30;
    tanks[1].y = SCREEN_H-30;
    tanks[1].speed = 0;
    tanks[1].score = 0;
    tanks[1].dir = 7;
    
    //load second tank bitmap
    tank_bmp[1][0] = load_bitmap("tank2.bmp", NULL);    
    
    //rotate image to generate all 8 directions
    for (n=1; n<8; n++)
    {
        tank_bmp[1][n] = create_bitmap(32, 32);
        clear_bitmap(tank_bmp[1][n]);
        rotate_sprite(tank_bmp[1][n], tank_bmp[1][0], 
            0, 0, itofix(n*32));
    }
}


/////////////////////////////////////////////////////////////////////
// setupscreen function
// set up the graphics mode and draw the game screen
/////////////////////////////////////////////////////////////////////
void setupscreen()
{
    int ret;

    //set video mode    
    set_color_depth(32);
    ret = set_gfx_mode(MODE, WIDTH, HEIGHT, 0, 0);
    if (ret != 0) {
        allegro_message(allegro_error);
        return;
    }

    //print title
    textprintf_ex(screen, font, 1, 1, BURST, 0,
        "Tank War - %dx%d", SCREEN_W, SCREEN_H);

    //draw screen border        
    rect(screen, 0, 12, SCREEN_W-1, SCREEN_H-1, TAN);
    rect(screen, 1, 13, SCREEN_W-2, SCREEN_H-2, TAN);
   
}

/////////////////////////////////////////////////////////////////////
// main function
// start point of the program
/////////////////////////////////////////////////////////////////////
int main(void)
{
    //initialize the game
    allegro_init(); 
    install_keyboard(); 
    install_timer();
    srand(time(NULL));
    setupscreen();
    setuptanks();

    //game loop
    while(!gameover)
    {
        textprintf_ex(screen, font, 0, SCREEN_H-10, WHITE, 0,
            "DIRS %d , %d", tanks[0].dir, tanks[1].dir);
        //erase the tanks
        erasetank(0);
        erasetank(1);
        
        //move the tanks
        movetank(0);
        movetank(1);

        //draw the tanks
        drawtank(0);
        drawtank(1);

        //update the bullets
        updatebullet(0);
        updatebullet(1);
        
        //check for keypresses
        if (keypressed())
            getinput();

        //slow the game down
        rest(10);
    }

    //end program
    allegro_exit();
    return 0;
}
END_OF_MAIN()
