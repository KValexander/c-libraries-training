#ifndef PLATFORM_H_
#define PLATFORM_H_

/* Include libraries */
#include <raylib.h>

/* Struct Platform */
typedef struct {
	int x, y, w, h; // char
} Platform;

/* Platform prototypes */
extern void platform_init(Platform *platform); // platform initialization
extern int platform_collision(Platform *platform, float x, float y, float w, float h); // platform collision
extern void platform_draw(Platform *platform, Texture2D *texture, Vector2 camera); // platform render

#endif