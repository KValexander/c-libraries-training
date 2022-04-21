/* Include libraries */
#include <stdio.h>

/* Include libraries */
#include <raylib.h>

/* Include files */
#include "level/surface.h"

/* Surface initialization */ 
void surface_init(Surface *surface) {

	surface->x = 0;
	surface->y = 0;
	surface->w = 400;
	surface->h = 64;

}

/* Surface render */ 
void surface_draw(Surface *surface, Texture2D *texture, Vector2 camera) {
	DrawTexture(
		*texture,
		camera.x + surface->x,
		camera.y + surface->y,
		WHITE
	);
}