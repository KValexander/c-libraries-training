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

	/* Hitbox */
	tile.hitbox.x = tile.rect.x + 5;
	tile.hitbox.y = tile.rect.y + 20;
	tile.hitbox.w = tile.rect.w - 10;
	tile.hitbox.h = tile.rect.h - 40;

	/* Color */
	tile.color = color;

	/* Onload texture */
	tile.onload_texture = 0; 

	/* Collision state */
	tile.collision = collision;

	/* Return tile */
	return tile;

}

/* Give texture */
void tile_give_texture(Tile *tile, MyTexture texture) {
	tile->texture = texture;
	tile->onload_texture = 1;
	tile->rect.w = tile->texture.w;
	tile->rect.h = tile->texture.h;
} 

/* Draw tile */
void tile_draw(Tile *tile, Position camera) {

	/* Draw texture */
	if(tile->onload_texture)
		DrawTexture(
			tile->texture.texture,
			camera.x + tile->rect.x,
			camera.y + tile->rect.y,
			WHITE
		);

	/* Draw rectangle */
	else DrawRectangle(
		camera.x + tile->rect.x,
		camera.y + tile->rect.y,
		tile->rect.w,
		tile->rect.h,
		tile->color
	);
}