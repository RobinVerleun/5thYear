#include <stdio.h>
#include <allegro.h>

#define WIDTH 640
#define HEIGHT 480
#define NUMBEROFSQUARES 34134

struct snakeBody {
	int x1, x2;
	int y1, y2;
	int isTail;
	int colour;
} body[NUMBEROFSQUARES];

//Prototyping
int init_game(int x, int y) {
	body[0].x1 = x;
	body[0].y1 = y;
	isTail = 1;
	colour = 10;
}
int shiftSnake(void);
int randomFood(void);
int detectCollision(void);
int readInput(void);

int main(void) {

	int gameover = 0;
	int snakeSize = 1;
	int rc;
	int x, y;
		
		//initialize allegro
		allegro_init();
		install_keyboard();

		srand(time(NULL));

		rc = set_gfx_mode(GFX_AUTODETECT_WINDOWED, WIDTH, HEIGHT, 0, 0);
		if(rc) {
			allegro_message("%s", allegro_error);
			return 1;
		}

		//initialize game
		x = rand() % WIDTH + 10;
		y = rand() % HEIGHT + 10;

		init_game(x, y);


		while(!key[KEY_ESC]) {
			

		}
	
	allegro_exit();
	return 0;

}
END_OF_MAIN();