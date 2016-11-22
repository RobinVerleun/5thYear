#include <stdio.h>
#include <allegro.h>

int main(void) {

	int k, x, y;
	int scancode, ascii;

	//initialize program
	allegro_init();
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
	install_keyboard();

	//display title
	textout_ex(screen, font, "KeyTest Program", 0, 0, 15, 0);
	textout_ex(screen, font, "Press key (ESC to quit)...", 0, 20, 15, 0);

	//set starting position for text
	x = SCREEN_W/2 - 60;
	y = SCREEN_H/2 - 20;

	while(!key[KEY_ESC]) {
		//get and convert scan code
		k = readkey();
		scancode = (k >> 8);
		ascii = scancode_to_ascii(scancode);

		//display key values
		textprintf_ex(screen, font, x, y, 15, 0,
			"Key value = %-6d", k);
		textprintf_ex(screen, font, x, y+15, 15, 0,
			"Scan code = %-6d", scancode);
		textprintf_ex(screen, font, x, y+30, 15, 0,
			"ASCII code = %-6d", ascii);
		textprintf_ex(screen, font, x, y+45, 15, 0,
			"Character = %-6c", (char)ascii);
	}
	allegro_exit();
	return 0;
}

END_OF_MAIN();