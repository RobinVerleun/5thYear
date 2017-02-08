/////////////////////////////////////////////////////////////////////
// Game Programming All In One, Third Edition
// Chapter 9 - Tank War Game (Enhancement 4)
/////////////////////////////////////////////////////////////////////

#include "tankwar.h"

int inside(int x,int y,int left,int top,int right,int bottom)
{
    if (x > left && x < right && y > top && y < bottom)
        return 1;
    else
        return 0;
}

int collided(SPRITE *a, SPRITE *b)
{
    int wa = a->x + a->width;
    int ha =a->y + a->height;
    int wb = b->x + b->width;
    int hb = b->y + b->height;
    int bx = 5;
    int by = 5;

    if (inside(a->x, a->y, b->x+bx, b->y+by, wb-bx, hb-by) ||
        inside(a->x, ha, b->x+bx, b->y+by, wb-bx, hb-by) ||
        inside(wa, a->y, b->x+bx, b->y+by, wb-bx, hb-by) ||
        inside(wa, ha, b->x+bx, b->y+by, wb-bx, hb-by))
        return 1;
    else
        return 0;
}

void drawtank(int num)
{
    int dir = tanks[num]->dir;
    int x = tanks[num]->x-15;
    int y = tanks[num]->y-15;
    draw_sprite(screen, tank_bmp[num][dir], x, y);
}

void erasetank(int num)
{
    int x = tanks[num]->x-17;
    int y = tanks[num]->y-17;
    rectfill(screen, x, y, x+33, y+33, BLACK);
}

void movetank(int num){
    int dir = tanks[num]->dir;
    int speed = tanks[num]->xspeed;

    //update tank position based on direction
    switch(dir)
    {
        case 0:
            tanks[num]->y -= speed;
            break;
        case 1:
            tanks[num]->x += speed;
            tanks[num]->y -= speed;
            break;
        case 2:
            tanks[num]->x += speed;
            break;
        case 3:
            tanks[num]->x += speed;
            tanks[num]->y += speed;
            break;
        case 4:
            tanks[num]->y += speed;
            break;
        case 5:
            tanks[num]->x -= speed;
            tanks[num]->y += speed;
            break;
        case 6:
            tanks[num]->x -= speed;
            break;
        case 7:
            tanks[num]->x -= speed;
            tanks[num]->y -= speed;
            break;
    }

    //keep tank inside the screen
    //use xspeed as a generic "speed" variable
    if (tanks[num]->x > SCREEN_W-22)
    {
        tanks[num]->x = SCREEN_W-22;
        tanks[num]->xspeed = 0;
    }
    if (tanks[num]->x < 22)
    {
        tanks[num]->x = 22;
        tanks[num]->xspeed = 0;
    }
    if (tanks[num]->y > SCREEN_H-22)
    {
        tanks[num]->y = SCREEN_H-22;
        tanks[num]->xspeed = 0;
    }
    if (tanks[num]->y < 22)
    {
        tanks[num]->y = 22;
        tanks[num]->xspeed = 0;
    }

    //see if tanks collided
/*    if (collided(tanks[0], tanks[1]))
    {
        textout(screen,font,"HIT",tanks[0]->x, tanks[0]->y,WHITE);
        tanks[0]->xspeed = 0;
        tanks[1]->xspeed = 0;
    }
    */
}

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

void updatebullet(int num)
{
    int x, y, tx, ty;
    int othertank;

    x = bullets[num]->x;
    y = bullets[num]->y;

    if (num == 1)
        othertank = 0;
    else
        othertank = 1;

    //is the bullet active?
    if (!bullets[num]->alive) return;
    
    //erase bullet
    rectfill(screen, x, y, x+10, y+10, BLACK); 

    //move bullet
    bullets[num]->x += bullets[num]->xspeed;
    bullets[num]->y += bullets[num]->yspeed;
    x = bullets[num]->x;
    y = bullets[num]->y;

    //stay within the screen
    if (x < 6 || x > SCREEN_W-6 || y < 20 || y > SCREEN_H-6)
    {
        bullets[num]->alive = 0;
        return;
    }

    //look for a direct hit using basic collision
    tx = tanks[!num]->x;
    ty = tanks[!num]->y;
    //if (collided(bullets[num], tanks[!num]))
    if (inside(x,y,tx,ty,tx+16,ty+16))
    {
        //kill the bullet
        bullets[num]->alive = 0;
            
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
        textprintf_ex(screen, font, SCREEN_W/2-50, 1, TAN, -1,
            "B1 %-3dx%-3d  B2 %-3dx%-3d", 
            bullets[0]->x, bullets[0]->y, 
            bullets[1]->x, bullets[1]->y);
    }
}

void fireweapon(int num)
{
    int x = tanks[num]->x;
    int y = tanks[num]->y;

    //ready to fire again?
    if (!bullets[num]->alive)
    {
        bullets[num]->alive = 1;

        //fire bullet in direction tank is facing
        switch (tanks[num]->dir)
        {
            //north
            case 0:
                bullets[num]->x = x-2;
                bullets[num]->y = y-22;
                bullets[num]->xspeed = 0;
                bullets[num]->yspeed = -BULLETSPEED;
                break;
            //NE
            case 1:
                bullets[num]->x = x+18;
                bullets[num]->y = y-18;
                bullets[num]->xspeed = BULLETSPEED;
                bullets[num]->yspeed = -BULLETSPEED;         
                break;  
            //east
            case 2:
                bullets[num]->x = x+22;
                bullets[num]->y = y-2;
                bullets[num]->xspeed = BULLETSPEED;
                bullets[num]->yspeed = 0;
                break;
            //SE
            case 3:
                bullets[num]->x = x+18;
                bullets[num]->y = y+18;
                bullets[num]->xspeed = BULLETSPEED;
                bullets[num]->yspeed = BULLETSPEED;
                break;
            //south
            case 4:
                bullets[num]->x = x-2;
                bullets[num]->y = y+22;
                bullets[num]->xspeed = 0;
                bullets[num]->yspeed = BULLETSPEED;
                break;
            //SW
            case 5:
                bullets[num]->x = x-18;
                bullets[num]->y = y+18;
                bullets[num]->xspeed = -BULLETSPEED;
                bullets[num]->yspeed = BULLETSPEED;
                break;
            //west
            case 6:
                bullets[num]->x = x-22;
                bullets[num]->y = y-2;
                bullets[num]->xspeed = -BULLETSPEED;
                bullets[num]->yspeed = 0;
                break;
            //NW
            case 7:
                bullets[num]->x = x-18;
                bullets[num]->y = y-18;
                bullets[num]->xspeed = -BULLETSPEED;
                bullets[num]->yspeed = -BULLETSPEED;
                break;
        }
    }
}

void forward(int num)
{
    //use xspeed as a generic "speed" variable
    tanks[num]->xspeed++;
    if (tanks[num]->xspeed > MAXSPEED)
        tanks[num]->xspeed = MAXSPEED;
}

void backward(int num)
{
    tanks[num]->xspeed--;
    if (tanks[num]->xspeed < -MAXSPEED)
        tanks[num]->xspeed = -MAXSPEED;
}

void turnleft(int num)
{
    tanks[num]->dir--;
    if (tanks[num]->dir < 0)
        tanks[num]->dir = 7;
}

void turnright(int num)
{
    tanks[num]->dir++;
    if (tanks[num]->dir > 7)
        tanks[num]->dir = 0;
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
    rest(20);
}

void score(int player)
{
    //update score
    int points = ++scores[player];

    //display score
    textprintf_ex(screen, font, SCREEN_W-70*(player+1), 1, -1,
        BURST, "P%d: %d", player+1, points);
}

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
        clear_bitmap(tank_bmp[0][n]);
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
        clear_bitmap(tank_bmp[1][n]);
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


}

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
    textprintf_ex(screen, font, 1, 1, BURST, -1,
        "Tank War - %dx%d", SCREEN_W, SCREEN_H);

    //draw screen border        
    rect(screen, 0, 12, SCREEN_W-1, SCREEN_H-1, TAN);
    rect(screen, 1, 13, SCREEN_W-2, SCREEN_H-2, TAN);
   
}

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
        rest(20);
    }

    //end program
    allegro_exit();
    return 0;
}
END_OF_MAIN()
