
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

#define COL_BACKGROUND makecol(255,255,153)
#define BLACK makecol(0,0,0)
#define NAVY makecol(0, 0, 102)

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
} question;

/* Globals */
int gamestop = 0;

question *questions = NULL;
int num_questions = 0;
int correct_answers = 0;
int *random_q;

SAMPLE *music, *correct, *incorrect;

/* Prototypes */
void initialize_sounds();
void play_sounds(int);
void initialize_screen(void);
void screen_drawbackground(void);
void screen_showintroduction(void);
void screen_promptuser(void);
void get_promptinput(void);
void shuffle_questions(void);
void screen_showquestion(int);
void get_questionanswer(int);
void screen_showscore(void);
void screen_endgame(void);
void read_textfile(char *);
void cleanup(void);

#endif