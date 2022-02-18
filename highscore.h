#ifndef HISCORE_H
#define HISCORE_H	1

#define HIGHSCORE_TABLE	10

#include <allegro.h>
#include <iostream>
#include <string.h>
#include <fstream>

extern BITMAP* buffer;
extern FONT* font_big;
extern FONT* font_interface;

void show_highscores(int, BITMAP*);
int save_highscore(char*, int);

#endif
