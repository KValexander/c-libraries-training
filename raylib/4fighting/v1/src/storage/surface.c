/* Include libraries */
#include <stdio.h>

/* Include libraries */
#include <raylib.h>

/* Include files */
#include "storage/surface.h"

/* Create surface */
Surface create_surface(int x, int y, int collision, MyTexture texture) {

	/* Create surface */
	Surface surface;

	/* Posititon */
	surface.x = x; 
	surface.y = y;

	/* State collision */
	surface.collision = collision;

	/* Texture */
	surface.texture = texture;

	/* Size */
	surface.w = surface.texture.w;
	surface.h = surface.texture.h;

	/* Return surface */
	return surface;

}

/* Draw surface */
void surface_draw(Surface *surface) {
	DrawTexture(
		surface->texture.texture,
		surface->x,
		surface->y,
		WHITE
	);
}