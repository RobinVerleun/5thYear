
#ifndef _MAIN_H_
#define _MAIN_H_

#include "allegro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Game Constants */
#define GFX_MODE GFX_AUTODETECT_WINDOWED
#define WIDTH 960
#define HEIGHT 720

#define COL_BACKGROUND makecol(0,150,255)
#define WHITE makecol(255,255,255)
#define RED makecol(255, 0, 0)

#define SUCCESS 0
#define FAILURE 1

#define BUFFSIZE 200

#define INTRODUCTION 0
#define CORRECT 1
#define INCORRECT 2

/* Structs */
typedef struct Questions {
	char q[BUFFSIZE];
	char answer_a[BUFFSIZE];
	char answer_b[BUFFSIZE];
	char answer_c[BUFFSIZE];
	char answer_d[BUFFSIZE];
	char correct_answer;
	int shown;
} question;

/* Prototypes */
void initialize_screen(void);
void setup_sounds();
void play_sounds(int);
void draw_background(void);
void show_introduction(void);
void prompt_userQuestion(void);
void get_prompt_input(void);
void shuffle_questions(void);
void show_question_screen(int);
void process_user_answer(int);
void show_score(void);
void read_textfile(char *);
void cleanup(void);

/* Globals */
int gameover = 0;

question *questions = NULL;
int num_questions = 0;
int correct_answers = 0;
int *random_q;

SAMPLE *music, *correct, *incorrect;



#endif