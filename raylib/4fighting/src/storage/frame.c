/* Include libraries */
#include <stdio.h>

/* Include libraries */
#include <raylib.h>

/* Include files */
#include "storage/frame.h"

/* Create frame */
Frame create_frame(Rect frame_display, Rect frame_hitbox) {

	/* Create frame */ 
	Frame frame;

	frame.display = frame_display; // display area
	frame.display = frame_hitbox; // hitbox area

	/* Return Frame */
	return frame;

}