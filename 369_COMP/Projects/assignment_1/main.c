/*
	One text file per chapter (unit 1, 2, 3)
	

	Things To Do!!!____
		-Prompt user for what questions they want - ALL, Chapters, Units
		-Store questions from the selected amount
			->Means that the number of questions will need to be known ahead of time
		-Allocate and store the questions based on the user selection into memory
		-Present a random question from the list to the user
		-Track score, show it on the screen as a ratio (x / y)


		-Show a welcome screen that explains the game and moves on after keypress


*/



#include "main.h"

int main(void) {

	/* Initialize everything */
	allegro_init();
	install_keyboard();
	install_timer();

	//setup_sounds();			/* Initialize sounds for music, correct, fail, and finished */
	initialize_screen();
	show_introduction();		/* Create the Introduction screen */
	prompt_userQuestion(); 		/* Get the users choice of question */
	shuffle_questions();		/* Generate a random order for the questions */

	int cur_q = 0;
	while(!gameover) {
		rest(150);
		show_question_screen(cur_q);
		cur_q++;
		if(key[KEY_ESC] || cur_q == 7) {
			gameover = 1;
		} //TODO: HERE, implementing answers and getting user input
	/*	
	int i,j;
	for(i = 0; i < num_questions; i++) {
		printf("Question: %s\n Answer 1: %s\n Answer 2: %s\n Answer 3: %s\n Answer 4: %s\n Correct: %d\n",
			questions[i].q, questions[i].answer_a, questions[i].answer_b,
			questions[i].answer_c, questions[i].answer_d, questions[i].correct_answer); 
	}
	*/
	allegro_exit();
	return 0;
}
END_OF_MAIN();

void initialize_screen() {
	/* set video mode */
	int rc = set_gfx_mode(GFX_MODE, WIDTH, HEIGHT, 0, 0);
	if( rc ) {
		allegro_message(allegro_error);	
		return;
	}

	textprintf_ex(screen, font, 1, 1, WHITE, -1, 
		"COMP 369 Quiz Machine! - %d x %d", WIDTH, HEIGHT);
}

void draw_background() {
	clear(screen);
	int x1 = 10;
	int y1 = 10;
	int x2 = WIDTH - 10;
	int y2 = HEIGHT - 10;
	int tri_side = x2 * 0.2;

	rectfill(screen, x1, y1, x2, y2, COL_BACKGROUND);
	triangle(screen, x1, y1, x1, y1+tri_side, x1+tri_side, y1, RED);
	triangle(screen, x1, y2, x1, y2-tri_side, x1+tri_side, y2, RED);
	triangle(screen, x2, y1, x2, y1+tri_side, x2-tri_side, y1, RED);
	triangle(screen, x2, y2, x2, y2-tri_side, x2-tri_side, y2, RED);
}

void show_introduction() {
	draw_background();

	int local_w = WIDTH / 2;
	int local_h = HEIGHT * 0.4;

	textprintf_centre_ex(screen, font, local_w, local_h, WHITE, -1,
		"Welcome to COMP 369 Quiz Machine!");
	textprintf_centre_ex(screen, font, local_w, local_h + 20, WHITE, -1,
		"Answer the multiple choice questions to the best");
	textprintf_centre_ex(screen, font, local_w, local_h + 30, WHITE, -1,
		"of your ability, and get a perfect score!");
	textprintf_centre_ex(screen, font, local_w, local_h + 50, WHITE, -1,
		"When a question appears, press the corresponding number to answer.");
	textprintf_centre_ex(screen, font, local_w, local_h + 80, WHITE, -1,
		"Press ENTER to continue.");

	while(!key[KEY_ENTER]) {}
	return;
}

void prompt_userQuestion() {
	draw_background();

	int local_w = WIDTH / 2;
	int local_h = HEIGHT * 0.4;
	int column1 = WIDTH * 0.33;
	int column2 = WIDTH * 0.55;

	textprintf_centre_ex(screen, font, local_w, local_h, WHITE, -1,
		"Please select which chapters or units you'd like to be quizzed on.");
	textprintf_centre_ex(screen, font, local_w, local_h + 10, WHITE, -1,
		"Or, do it all!");

	/* Row 1 */
	textprintf_ex(screen, font, column1, local_h + 50, WHITE, -1,
		"A) Chapter 1");
	textprintf_ex(screen, font, column2, local_h + 50, WHITE, -1,
		"B) Chapter 2");

	/* Row 2 */
	textprintf_ex(screen, font, column1, local_h + 60, WHITE, -1,
		"C) Chapter 3");
	textprintf_ex(screen, font, column2, local_h + 60, WHITE, -1,
		"D) Chapter 4");

	/* Row 3 */
	textprintf_ex(screen, font, column1, local_h + 70, WHITE, -1,
		"E) Chapter 5");
	textprintf_ex(screen, font, column2, local_h + 70, WHITE, -1,
		"F) Chapter 6");

	/* Row 4 */
	textprintf_ex(screen, font, column1, local_h + 80, WHITE, -1,
		"G) Chapter 17");
	textprintf_ex(screen, font, column2, local_h + 80, WHITE, -1,
		"H) Unit 1");

	/* Row 5 */
	textprintf_ex(screen, font, column1, local_h + 90, WHITE, -1,
		"I) Unit 2");
	textprintf_ex(screen, font, column2, local_h + 90, WHITE, -1,
		"J) Unit 3");

	/* Row 6 */
	textprintf_ex(screen, font, column1, local_h + 100, WHITE, -1,
		"K) Everything");

	get_prompt_input();
}

void get_prompt_input() {

	while(1) {

		if(key[KEY_ESC]) {  	/* Hit ESC to quit */
			gameover = 1;
			break;
		}
		if(key[KEY_A]) {		/* Load Chapter 1 */
			read_textfile("./questions/chapter1.txt");
			break;
		}
		if(key[KEY_B]) {		/* Load Chapter 2 */
			read_textfile("./questions/chapter2.txt");
			break;
		}
		if(key[KEY_C]) {		/* Load Chapter 3 */
			read_textfile("./questions/chapter3.txt");
			break;
		}
		if(key[KEY_D]) {		/* Load Chapter 4 */
			read_textfile("./questions/chapter4.txt");
			break;
		}
		if(key[KEY_E]) {		/* Load Chapter 5 */
			read_textfile("./questions/chapter5.txt");
			break;
		}
		if(key[KEY_F]) {		/* Load Chapter 6 */
			read_textfile("./questions/chapter6.txt");
			break;
		}
		if(key[KEY_G]) {		/* Load Chapter 17 */
			read_textfile("./questions/chapter17.txt");
			break;
		}
		if(key[KEY_H]) {		/* Load Unit 1 (Chapter 1,2,3) */
			read_textfile("./questions/chapter1.txt");
			read_textfile("./questions/chapter2.txt");
			read_textfile("./questions/chapter3.txt");
			break;
		}
		if(key[KEY_I]) {		/* Load Unit 2 (Chapter 4,5,6) */
			read_textfile("./questions/chapter4.txt");
			read_textfile("./questions/chapter5.txt");
			read_textfile("./questions/chapter6.txt");
			break;
		}
		if(key[KEY_J]) {		/* Load Unit 3 (Chapter 17) */
			read_textfile("./questions/chapter17.txt");
			break;
		}
		if(key[KEY_K]) {		/* Load all chapters */
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
void show_question_screen(int index) {
	draw_background();

	int local_w = WIDTH / 2;
	int local_h = HEIGHT * 0.4;

	textprintf_centre_ex(screen, font, local_w, local_h, WHITE, -1,
		"%s",questions[random_q[index]].q);


	while(!key[KEY_ENTER]) {}
	rest(300);
	return;
}

void read_textfile(char *filepath) {

	FILE *ptr_file;
	char *buf = malloc(BUFFSIZE);
	int current = num_questions;
	int i, j;
	
	ptr_file = fopen(filepath, "r");
	if(!ptr_file){
		return;
	}
	
	/*
	 * Each question will have 6 lines. First line will be the number of questions 
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
		cur_question.shown = 0;

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
					cur_question.correct_answer = atoi(buf);
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
}

//Unit 1, Unit 2, Unit 3, All, Chapter 1-6, Chapter 17