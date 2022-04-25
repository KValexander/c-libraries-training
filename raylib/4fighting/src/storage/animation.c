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

/* Animation play */
void animation_play(Animation *animation, int time) {

	/* Current frame */ 
	if(time % animation->time == 0) {
		animation->current_frame = (animation->current_frame < animation->count_frames - 1)
									? ++animation->current_frame : 0;
	}

}

/* Animation display */
Rect animation_display(Animation *animation) {

	Rect display = {
		animation->start.x + animation->frames[animation->current_frame].display.x, 
		animation->start.y + animation->frames[animation->current_frame].display.y,
		animation->frames[animation->current_frame].display.w,
		animation->frames[animation->current_frame].display.h
	};

	return display;
}