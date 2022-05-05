/* Include libraries */
#include <stdio.h>

/* Include files */
#include "tile.h"

/* Create tile */
Tile create_tile(Rect rect, Color color, int collision) {

	/* Create tile */
	Tile tile;

	/* Rect */
	tile.rect = rect;

	/* Color */
	tile.color = color;

	/* Collision state */
	tile.collision = collision;

	/* Return tile */
	return tile;

}

/* Draw tile */
void tile_draw(Tile *tile, Position camera) {
	DrawRectangle(
		camera.x + tile->rect.x,
		camera.y + tile->rect.y,
		tile->rect.w,
		tile->rect.h,
		tile->color
	);
}