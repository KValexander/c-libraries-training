#ifndef ANIMATION_H_
#define ANIMATION_H_

/* Constants */
#define MAX_FRAMES 10

/* Include libraries */
#include <raylib.h>

/* Include files */
#include "common.h"
#include "storage/frame.h"

/* Struct Animation */ 
typedef struct Animation {

	char name[255]; // animation name
	int time; // animation time
	Position start; // animation start position on the texture

	/* Frames */ 
	int count_frames; // count frames
	int current_frame; // current frame
	Frame frames[MAX_FRAMES]; // animation frames

} Animation;

/* Prototypes */
/* Create animation */ 
extern Animation create_animation(char *name, int time, int count_frames, Frame frames[MAX_FRAMES], int x, int y);

/* Animation play */
extern void animation_play(Animation *animation, int time);

/* Animation display */
extern Rect animation_display(Animation *animation);

#endif