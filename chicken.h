#ifndef CHICKEN_H
#define CHICKEN_H	1

#include <allegro.h>
#include "animation.h"
#include "gore.h"

#define CROSSED_THE_ROAD	2

extern float CHICKEN_SPEED;
extern int MAX_CHICKENS;
extern DATAFILE* chicken_data;
extern DATAFILE* flyingchicken_data;
extern LEVEL level;

class CHICKEN {

	public:
	
	CHICKEN();
	void draw();
	void reset();
	int run();
	
	KFC dead;
	ANIMATION running;
	ANIMATION flying;

	float x;
	float y;
	float y_vel;
	int direction;
	int flight;
	int alive;
};

#endif
