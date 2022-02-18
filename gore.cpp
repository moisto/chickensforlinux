#include "gore.h"

void BLOOD::release(float X, float Y, float X_VEL, float Y_VEL) {
	x = X + rand() % 10 - rand() % 10;
	y = Y + rand() % 10 - rand() % 10;
	x_vel = X_VEL + float(rand()%5)/float(1 + rand()%10) * (rand() % 2 == 1 ? 1:-1);
	y_vel = Y_VEL + float(rand()%5)/float(1 + rand()%10) * (rand() % 2 == 1 ? 1:-1);
}

void BLOOD::run() {
	y_vel += GRAVITY;
	x += x_vel;
	y += y_vel;
}

void BLOOD::draw() {
	if (x >= 0 && x < SCREEN_W)
		if (y >= 0 && y < SCREEN_H)
			putpixel(buffer, (int)x, (int)y, makecol(220, 0, 0));
}





GIBLET::GIBLET() {
	image = rand() % items_in_datafile(giblet_data);
	landed = false;
}



KFC::KFC() {
	released = false;
}


void KFC::explode() {
	
	if (released) {
		
		for (int i = 0; i < CHUNKS_PER_CHICKEN; ++i) {
			
			
			// If the chunk is visible on the screen
			if (chunk[i].x >= 0 && chunk[i].x < SCREEN_W) { // Thank you Jarno!
			
				// If it hit the ground
				if (chunk[i].y >= SCREEN_H - level.height[(int)chunk[i].x]) {
				
					chunk[i].y = SCREEN_H - level.height[(int)chunk[i].x];
					chunk[i].x_vel = int(chunk[i].x_vel * 0.3);
					chunk[i].y_vel = -int(chunk[i].y_vel * 0.3);
					
					// If the chunk has landed for good
					if (!chunk[i].landed && chunk[i].y_vel == 0 && chunk[i].x_vel == 0) {
						
						chunk[i].landed = true;
						
						for (int j = 0; j < 10; ++j) {
							int v = (int)chunk[i].x + j;
							
							if (v < SCREEN_W-1 && v > 0)
								if (level.height[v] - level.height[v-1] < 1)
									if (level.height[v] - level.height[v+1] < 1)
										level.height[v]++;
						}
						
						// If the chunk is visible on the screen
						if (chunk[i].x >= 0 && chunk[i].x < SCREEN_W)
							draw_sprite(level.image, (BITMAP*)giblet_data[chunk[i].image].dat, (int)chunk[i].x, MAX_LEVELHEIGHT - level.height[(int)chunk[i].x]);
					}
					
				}
			} else
				chunk[i].landed = true;
			
			chunk[i].y_vel += GRAVITY;
			
			chunk[i].x += chunk[i].x_vel;
			chunk[i].y += chunk[i].y_vel;
			
			
			for (int j = 0; j < BLOOD_PER_CHUNK; ++j)
				chunk[i].blood[j].run();
		}
	
	}
}


void KFC::draw() {
	if (released) {
	
		for (int i = 0; i < CHUNKS_PER_CHICKEN; ++i) {
		
			if (chunk[i].landed == false)
				draw_sprite(buffer, (BITMAP*)giblet_data[chunk[i].image].dat, (int)chunk[i].x, (int)chunk[i].y);
			
			for (int j = 0; j < BLOOD_PER_CHUNK; ++j)
				chunk[i].blood[j].draw();
		}
	
	}
}


void KFC::release(float at_x, float at_y, int accuracy, int death, int direction) {
	
	chunk = new GIBLET[CHUNKS_PER_CHICKEN];
	
	accuracy -= CHICKEN_WIDTH/2; // Base accuracy off the center of chicken, not its actual x position.
	
	for (int i = 0; i < CHUNKS_PER_CHICKEN; ++i) {
		
		chunk[i].blood = new BLOOD[BLOOD_PER_CHUNK];
		
		chunk[i].landed = false;
		chunk[i].x = at_x + rand() % CHICKEN_WIDTH;
		chunk[i].y = at_y + rand() % CHICKEN_HEIGHT;
		
		switch (death) {
			case KILLED_WITH_ROCKET:
				chunk[i].x_vel = float(rand()%5)/float(1 + rand()%10) * (rand() % 2 == 1 ? 1:-1) + (at_x - accuracy)/3;
				chunk[i].y_vel = -ROCKET_SIZE/3 - rand() % 6;
				break;
			case KILLED_WITH_SHOTGUN:
				chunk[i].x_vel = CHICKEN_SPEED * direction + rand()% 4 - rand() % 4;
				chunk[i].y_vel = -rand() % 6;
				break;
			case KILLED_WITH_TENDERIZER:
				chunk[i].x_vel = CHICKEN_SPEED * direction;
				chunk[i].y_vel = -rand() % 25 - 5;
				break;
		}
		
		for (int j = 0; j < BLOOD_PER_CHUNK; ++j)
			chunk[i].blood[j].release(chunk[i].x, chunk[i].y, chunk[i].x_vel, chunk[i].y_vel);
	}
	
	released = true;
}
