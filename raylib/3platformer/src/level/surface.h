#ifndef SURFACE_H_
#define SURFACE_H_

/* Include libraries */
#include <raylib.h>

/* Struct Surface */
typedef struct {
	int x, y, w, h; // char
} Surface;

/* Surface prototypes */
extern void surface_init(Surface *surface); // surface initialization
extern int surface_collision(Surface *surface, float x, float y, float w, float h); // surface collision
extern void surface_draw(Surface *surface, Texture2D *texture, Vector2 camera); // surface render

#endif