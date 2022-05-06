#ifndef TILE_H_
#define TILE_H_

/* Include libraries */
#include <raylib.h>

/* Include files */
#include "common.h"
#include "textures.h"

/* Struct Tile */
typedef struct Tile {
	Rect rect; 	 // x, y, w, h
	Rect hitbox; // hitbox
	Color color; // color

	int onload_texture; // onload texture
	MyTexture texture; // texture

	int collision; // collision state
} Tile;

/* Prototypes */

/* Create tile */ 
extern Tile create_tile(Rect rect, Color color, int collision);

/* Give texture */ 
extern void tile_give_texture(Tile *tile, MyTexture texture);

/* Draw tile */
extern void tile_draw(Tile *tile, Position camera);

#endif