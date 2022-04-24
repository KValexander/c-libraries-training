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
	Texture2D *texture; // texture

	/* Frames */ 
	int count_frames; // count frames
	int current_frame; // current frame
	Frame frames[MAX_FRAMES]; // animation frames

} Animation;

#endif