/* Include libraries */
#include <stdio.h>

/* Include libraries */
#include <raylib.h>

/* Include files */
#include "helpers.h"
#include "level/surface.h"

/* Surface initialization */ 
void surface_init(Surface *surface) {

	surface->x = 0;
	surface->y = 0;
	surface->w = 400;
	surface->h = 64;

}

/* Surface collision */
int surface_collision(Surface *surface, float x, float y, float w, float h){
	
	/* Getting the side of the collision */
	return sides_collision(x, y, surface->x, surface->y, w, h, surface->w, surface->h);
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