#ifndef FRAME_H_
#define FRAME_H_

/* Include files */
#include "common.h"

/* Struct Frame */ 
typedef struct Frame {
	Rect display; // display area
	Rect hitbox; // hitbox area
} Frame;

/* Prototypes */
extern Frame create_frame(int pw, int ph, int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);

#endif