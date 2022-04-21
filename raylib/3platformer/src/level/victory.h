#ifndef VICTORY_H_
#define VICTORY_H_

/* Include libraries */
#include <raylib.h>

/* Struct Victory */
typedef struct {
	int x, y, w, h; // char
} Victory;

/* Victory prototypes */
extern void victory_init(Victory *victory); // victory initialization
extern void victory_draw(Victory *victory, Texture2D *texture, Vector2 camera); // victory render

#endif