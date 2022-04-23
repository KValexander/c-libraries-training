#ifndef COMMON_H_
#define COMMON_H_

/* Constants */
#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 540
#define FPS 60

/* Prototypes */

/* Check collision */ 
extern int check_collision(float x1, float y1,
					  	   float x2, float y2,
					  	   float w1, float h1,
					 	   float w2, float h2);



#endif