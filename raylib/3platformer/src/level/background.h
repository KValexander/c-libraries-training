#ifndef BACKGROUND_H_
#define BACKGROUND_H_

/* Constants */ 
#define NUM_BACKGROUNDS 2

/* Include libraries */
#include <raylib.h>

/* Struct Background */
typedef struct {
	Texture2D image;
	float scroll, scroll_speed;
	float w, h;
} Background;

/* Background prototypes */
extern void background_init(Background *background);
extern void background_deinit(Background *background);
extern void background_update(Background *background);
extern void background_draw(Background *background);

#endif