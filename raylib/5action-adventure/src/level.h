#ifndef LEVEL_H_
#define LEVEL_H_

/* Constants */
#define MAX_TILES 1000

/* Include libraries */
#include <raylib.h>

/* Include files */
#include "common.h"
#include "player.h"
#include "tile.h"

/* Struct Level */
typedef struct Level {
	int frame; // time
	Position camera; // camera

	/* Player */
	int player_onload; // player onload state
	Player player; // player

	/* Tiles */ 
	int count_tiles; // count tiles
	Tile tiles[MAX_TILES]; // tiles
} Level;

/* Prototypes */

/* Initialization */
extern void level_init(Level *level);

/* Create tile */ 
extern void level_create_tile(Level *level, Position pos, Color color, int collision);

/* Create player */ 
extern void level_create_player(Level *level, Position pos, Color color, int speed);

/* Create map */ 
extern void level_create_map(Level *level);

/* Update */
extern void level_update(Level *level); 

/* Render */ 
extern void level_render(Level *level);

#endif