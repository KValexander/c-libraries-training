/* Include libraries */
#include <stdio.h>
#include <string.h>

/* Include libraries */
#include <raylib.h>

/* Include files */
#include "storage/animation.h"


/* Create animation */
Animation create_animation(char *name, int time, int count_frames, Frame frames[MAX_FRAMES], int x, int y) {

	/* Create animation */
	Animation animation;

	/* Naming */ 
	strcpy(animation.name, name);

	/* Data */ 
	animation.time = time; // time 
	animation.count_frames = count_frames; // count frames
	animation.current_frame = 0; // current frame

	/* Start position */
	animation.start.x = x;
	animation.start.y = y;

	/* Frames */
	for(int i = 0; i < animation.count_frames; i++)
		animation.frames[i] = frames[i];

	/* Return animation */
	return animation;

}

/* Create animation with frames */
Animation create_animation_with_frames(char *name, int time, int count_frames, int x, int y) {



}