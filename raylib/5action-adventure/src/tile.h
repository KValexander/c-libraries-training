#ifndef TILE_H_
#define TILE_H_

/* Include libraries */
#include <raylib.h>

/* Include files */
#include "common.h"

/* Struct Tile */
typedef struct Tile {
	Rect rect; 	 // x, y, w, h
	Color color; // color

	int collision; // collision state
} Tile;

/* Prototypes */

/* Create tile */ 
extern Tile create_tile(Rect rect, Color color, int collision);

/* Draw tile */
extern void tile_draw(Tile *tile, Position camera);

#endif