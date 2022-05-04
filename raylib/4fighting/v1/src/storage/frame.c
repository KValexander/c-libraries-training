/* Include libraries */
#include <stdio.h>

/* Include libraries */
#include <raylib.h>

/* Include files */
#include "storage/frame.h"

/* Create frame */
Frame create_frame(int pw, int ph, int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2){
	/* Create rects */ 
	Rect frame_display = {pw + x1, ph + y1, w1, h1};
	Rect frame_hitbox = {x2, y2, w2, h2};

	/* Create frame */ 
	Frame frame;
	frame.display = frame_display; // display area
	frame.hitbox = frame_hitbox; // hitbox area

	/* Return Frame */
	return frame;
}