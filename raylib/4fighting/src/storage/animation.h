#ifndef ANIMATION_H_
#define ANIMATION_H_

/* Constants */
#define MAX_FRAMES 10

/* Include files */
#include "storage/frame.h"

/* Struct Animation */ 
typedef struct Animation {

	char name[255]; // animation name

	/* Frames */ 
	int count_frames; // count frames
	int current_frame; // current frame
	Frame frames[MAX_FRAMES]; // animation frames

} Animation;

#endif