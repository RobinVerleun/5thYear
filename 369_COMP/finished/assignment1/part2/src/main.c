
#include "main.h"

int main(void) {

	// Initialize everything 
	allegro_init();
	allegro_404_char = ' ';
	install_keyboard();
	install_timer();

	initialize_sounds();			// Initialize sounds for music, correct, fail, and finished 
	play_sounds(INTRODUCTION);		// Start the backgroun music
	initialize_screen();			// Load the allegro screen requirements
	screen_showintroduction();		// Create the Introduction screen 
	screen_promptuser(); 			// Get the users choice of question 
	shuffle_questions();			// Generate a random order for the questions 

	int cur_q = 0;
	while(!gamestop) {
		rest(150);

		if(key[KEY_ESC]) {
			gamestop = 1;
			break;
		} else if(cur_q == num_questions) {
			break;
		}

		screen_showquestion(cur_q);			// Show the current question
		get_questionanswer(cur_q);			// Get and check the answer to the question
		cur_q++;
	}

	if(!gamestop) {
		screen_endgame();
	}

	cleanup();
	allegro_exit();
	return 0;
}
END_OF_MAIN();


void initialize_sounds() {

	if(install_sound(DIGI_AUTODETECT, MIDI_NONE,"") != 0) {
		allegro_message("Error initializing the sound system\n%s\n", allegro_error);
		return;
	}

	//load the wav files
	music = load_sample("./sounds/soundtrack.wav");
	if(!music) {
		allegro_message("Error loading music file.");
		return;
	}
	correct = load_sample("./sounds/correct.wav");
	if(!correct) {
		allegro_message("Error loading correct soundfile.");
		return;
	}
	incorrect = load_sample("./sounds/incorrect.wav");
	if(!incorrect) {
		allegro_message("Error loading incorrect soundfile.");
		return;
	}
}

void play_sounds(int sound_choice) {
	int panning = 128;
	int pitch = 1000;
	int volume = 128;

	if(sound_choice == INTRODUCTION) {
		play_sample(music, volume, panning, pitch, TRUE);
		return;
	}
	if(sound_choice == CORRECT) {
		play_sample(correct, volume, panning, pitch, FALSE);
		return;
	}
	if(sound_choice == INCORRECT) {
		play_sample(incorrect, volume, panning, pitch, FALSE);
	}
}

void initialize_screen() {
	/* set video mode */
	int rc = set_gfx_mode(GFX_MODE, WIDTH, HEIGHT, 0, 0);
	if( rc ) {
		allegro_message(allegro_error);	
		return;
	}

	textprintf_ex(screen, font, 1, 1, BLACK, -1, 
		"COMP 369 Quiz Machine! - %d x %d", WIDTH, HEIGHT);
}

void screen_drawbackground() {
	clear(screen);
	int x1 = 10;
	int y1 = 10;
	int x2 = WIDTH - 10;
	int y2 = HEIGHT - 10;
	int tri_side = x2 * 0.2;

	rectfill(screen, x1, y1, x2, y2, COL_BACKGROUND);
	triangle(screen, x1, y1, x1, y1+tri_side, x1+tri_side, y1, NAVY);
	triangle(screen, x1, y2, x1, y2-tri_side, x1+tri_side, y2, NAVY);
	triangle(screen, x2, y1, x2, y1+tri_side, x2-tri_side, y1, NAVY);
	triangle(screen, x2, y2, x2, y2-tri_side, x2-tri_side, y2, NAVY);
}

void screen_showintroduction() {
	screen_drawbackground();

	int local_w = WIDTH / 2;
	int local_h = HEIGHT * 0.4;

	textprintf_centre_ex(screen, font, local_w, local_h, BLACK, -1,
		"Welcome to COMP 369 Quiz Machine!");
	textprintf_centre_ex(screen, font, local_w, local_h + 20, BLACK, -1,
		"Answer the multiple choice questions to the best");
	textprintf_centre_ex(screen, font, local_w, local_h + 30, BLACK, -1,
		"of your ability, and get a perfect score!");
	textprintf_centre_ex(screen, font, local_w, local_h + 50, BLACK, -1,
		"When a question appears, press the corresponding number to answer.");
	textprintf_centre_ex(screen, font, local_w, local_h + 80, BLACK, -1,
		"Press ENTER to continue.");

	while(!key[KEY_ENTER] && !key[KEY_ESC]) {
		if(key[KEY_ESC]) {
			gamestop = 1;
			return;
		}
	}
}

void screen_promptuser() {
	
	screen_drawbackground();

	int local_w = WIDTH / 2;
	int local_h = HEIGHT * 0.4;
	int column1 = WIDTH * 0.33;
	int column2 = WIDTH * 0.55;

	textprintf_centre_ex(screen, font, local_w, local_h, BLACK, -1,
		"Please select which chapters or units you'd like to be quizzed on.");
	textprintf_centre_ex(screen, font, local_w, local_h + 10, BLACK, -1,
		"Or, do it all!");

	/* Row 1 */
	textprintf_ex(screen, font, column1, local_h + 50, BLACK, -1,
		"A) Chapter 1");
	textprintf_ex(screen, font, column2, local_h + 50, BLACK, -1,
		"B) Chapter 2");

	/* Row 2 */
	textprintf_ex(screen, font, column1, local_h + 60, BLACK, -1,
		"C) Chapter 3");
	textprintf_ex(screen, font, column2, local_h + 60, BLACK, -1,
		"D) Chapter 4");

	/* Row 3 */
	textprintf_ex(screen, font, column1, local_h + 70, BLACK, -1,
		"E) Chapter 5");
	textprintf_ex(screen, font, column2, local_h + 70, BLACK, -1,
		"F) Chapter 6");

	/* Row 4 */
	textprintf_ex(screen, font, column1, local_h + 80, BLACK, -1,
		"G) Chapter 17");
	textprintf_ex(screen, font, column2, local_h + 80, BLACK, -1,
		"H) Unit 1");

	/* Row 5 */
	textprintf_ex(screen, font, column1, local_h + 90, BLACK, -1,
		"I) Unit 2");
	textprintf_ex(screen, font, column2, local_h + 90, BLACK, -1,
		"J) Unit 3");

	/* Row 6 */
	textprintf_ex(screen, font, column1, local_h + 100, BLACK, -1,
		"K) Everything");

	get_promptinput();
}

void get_promptinput() {

	clear_keybuf();

	while(1) {

		if(key[KEY_ESC]) {  	// Hit ESC to quit
			gamestop = 1;
			break;
		}
		if(key[KEY_A]) {		// Load Chapter 1 
			read_textfile("./questions/chapter1.txt");
			break;
		}
		if(key[KEY_B]) {		// Load Chapter 2 
			read_textfile("./questions/chapter2.txt");
			break;
		}
		if(key[KEY_C]) {		// Load Chapter 3 
			read_textfile("./questions/chapter3.txt");
			break;
		}
		if(key[KEY_D]) {		// Load Chapter 4 
			read_textfile("./questions/chapter4.txt");
			break;
		}
		if(key[KEY_E]) {		// Load Chapter 5 
			read_textfile("./questions/chapter5.txt");
			break;
		}
		if(key[KEY_F]) {		// Load Chapter 6 
			read_textfile("./questions/chapter6.txt");
			break;
		}
		if(key[KEY_G]) {		// Load Chapter 17 
			read_textfile("./questions/chapter17.txt");
			break;
		}
		if(key[KEY_H]) {		// Load Unit 1 (Chapter 1,2,3) 
			read_textfile("./questions/chapter1.txt");
			read_textfile("./questions/chapter2.txt");
			read_textfile("./questions/chapter3.txt");
			break;
		}
		if(key[KEY_I]) {		// Load Unit 2 (Chapter 4,5,6) 
			read_textfile("./questions/chapter4.txt");
			read_textfile("./questions/chapter5.txt");
			read_textfile("./questions/chapter6.txt");
			break;
		}
		if(key[KEY_J]) {		// Load Unit 3 (Chapter 17) 
			read_textfile("./questions/chapter17.txt");
			break;
		}
		if(key[KEY_K]) {		// Load all chapters 
			read_textfile("./questions/chapter1.txt");
			read_textfile("./questions/chapter2.txt");
			read_textfile("./questions/chapter3.txt");
			read_textfile("./questions/chapter4.txt");
			read_textfile("./questions/chapter5.txt");
			read_textfile("./questions/chapter6.txt");
			read_textfile("./questions/chapter17.txt");
			break;
		}
	}
}

void shuffle_questions() {

	random_q = malloc(num_questions * sizeof(int));
	int i,j,k;
    int aux;
    srand(time(NULL));

    if(1 == num_questions) {
    	random_q[0] = 0;
    	return;
    }

    for(i = 0; i < num_questions; i++) {
    	random_q[i] = i;
    }

   /*
	* Credit to stackoverflow user Noxbru for the shuffling algorithm.
	* http://stackoverflow.com/questions/14985737/how-to-access-a-c-array-in-random-order-ensuring-that-all-elements-are-visited-a
	*/
    j = k = 0;
    for(i=0; i < num_questions; i++)
    {
        do
        {	
            j=rand() % num_questions;
            k=rand() % num_questions;
        } while (j == k);

        aux = random_q[j];
        random_q[j] = random_q[k];
        random_q[k] = aux;
    }
}

void screen_showquestion(int index) {
	
	screen_drawbackground();
	screen_showscore();

	int local_w = WIDTH / 2;
	int local_h = HEIGHT * 0.4;
	int column1 = WIDTH * 0.4;
	int column2 = WIDTH * 0.55;

	int q_len = strlen(questions[random_q[index]].q);


	if(q_len > 75) {	
		
		int i, last_space;
		char temp1[q_len/2 + 1];
		char temp2[q_len/2 + 1];
		memset(temp1, '\0', q_len/2 + 1);
		memset(temp2, '\0', q_len/2 + 1);

		for(int i = 0; i < 75; i++) {
			if(questions[random_q[index]].q[i] == ' ') {
				last_space = i;
			}
		}
		strncpy(temp1, questions[random_q[index]].q, last_space);
		strncpy(temp2, &questions[random_q[index]].q[last_space], q_len - last_space);

		textprintf_centre_ex(screen, font, local_w, local_h, BLACK, -1,
			"%s", temp1);	
		textprintf_centre_ex(screen, font, local_w, local_h + 10, BLACK, -1,
			"%s", temp2);

	} else {

		textprintf_centre_ex(screen, font, local_w, local_h, BLACK, -1,
			"%s", questions[random_q[index]].q);
	}

	textprintf_centre_ex(screen, font, local_w, local_h + 50, BLACK, -1,
		"1) %s", questions[random_q[index]].answer_a);
	textprintf_centre_ex(screen, font, local_w, local_h + 70, BLACK, -1,
		"2) %s", questions[random_q[index]].answer_b);
	textprintf_centre_ex(screen, font, local_w, local_h + 90, BLACK, -1,
		"3) %s", questions[random_q[index]].answer_c);
	textprintf_centre_ex(screen, font, local_w, local_h + 110, BLACK, -1,
		"4) %s", questions[random_q[index]].answer_d);

	return;
}

void get_questionanswer(int index) {

	clear_keybuf();
	int u_input;
	char u_answer;

	while(1) {

		u_input = readkey();
		u_input = scancode_to_ascii(u_input >> 8);
		u_answer = (char)u_input;

		if(u_answer == '1' || u_answer == '2' || u_answer == '3' || u_answer == '4') {
			if(u_answer == questions[random_q[index]].correct_answer){
				correct_answers++;
				play_sounds(CORRECT);
				//TODO: Show correct answer screen?
				break;
			} else { 
				//TODO: Show incorrect answer screen?
				play_sounds(INCORRECT);
				break;
			}
		}
	}
}

void screen_showscore() {
	int width = WIDTH / 2;
	textprintf_ex(screen, font, width - 10, HEIGHT * 0.2, BLACK, -1,
		"%d", correct_answers);
	textprintf_ex(screen, font, width + 10, HEIGHT * 0.22, BLACK, -1,
		"%d", num_questions);
	line(screen, width + 10, HEIGHT * 0.2, width - 10, HEIGHT * 0.24, BLACK);
}

void screen_endgame() {
	clear_keybuf();
	screen_drawbackground();
	int local_w = WIDTH / 2;
	int local_h = HEIGHT / 2;

	textprintf_centre_ex(screen, font, local_w, local_h, BLACK, -1,
		"You've reached the end of the available questions!");

	if(correct_answers == num_questions) {
		textprintf_centre_ex(screen, font, local_w, local_h + 20, BLACK, -1,
		"You scored 100%%! Congratulations!");
	} else {
		textprintf_centre_ex(screen, font, local_w, local_h + 20, BLACK, -1,
			"Your final score is %d / %d", correct_answers, num_questions);
		textprintf_centre_ex(screen, font, local_w, local_h + 40, BLACK, -1,
			"Try again and aim for 100%%!");
	}

	textprintf_centre_ex(screen, font, local_w, local_h + 60, BLACK, -1,
		"Press any key to exit.");

	int key = 0;
	while(!key) {
		key = readkey();
	}
}

void read_textfile(char *filepath) {

	FILE *ptr_file;
	char *buf = malloc(BUFFSIZE);
	int current = num_questions;
	int i, j;
	
	ptr_file = fopen(filepath, "r");
	if(!ptr_file){
		fprintf(stderr, "Could not open file %s\n", filepath);
		return;
	}
	
	/*
	 * Each question will have 6 lines. First line of the file will be the number of questions 
	 * Read the first line and get the number of questions
	 * Allocate space for the questions, dynamically growing array if needed
	 * then keep reading through the file and assigning questions.
	 */

	if(fgets(buf, BUFFSIZE, ptr_file) != NULL) {
		num_questions += atoi(buf);
		questions = realloc(questions, num_questions * sizeof(question));
	}
	
	for(i = current; i < num_questions; i++) {
		question cur_question;

		for(j = 0; j < 6; j++) {
			if(fgets(buf, BUFFSIZE, ptr_file) != NULL) {
				if(j == 0)
					strcpy(cur_question.q, buf);
				if(j == 1)
					strcpy(cur_question.answer_a, buf);
				if(j == 2)
					strcpy(cur_question.answer_b, buf);
				if(j == 3)
					strcpy(cur_question.answer_c, buf);
				if(j == 4)
					strcpy(cur_question.answer_d, buf);
				if(j == 5)
					cur_question.correct_answer = buf[0];
			}
		}

		questions[i] = cur_question;
	}
	fclose(ptr_file);
	free(buf);
}

void cleanup() {
	free(random_q);
	free(questions);
	destroy_sample(music);
	destroy_sample(correct);
	destroy_sample(incorrect);
	remove_sound();
}
