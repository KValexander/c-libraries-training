#ifndef LEVEL_H_
#define LEVEL_H_

/* Constants */
#define MAX_TILES 1000
#define MAX_LAYOUTS 10
#define MAX_ROWS 100
#define MAX_COLUMNS 100

/* Include libraries */
#include <raylib.h>

/* Include files */
#include "common.h"
#include "textures.h"
#include "player.h"
#include "tile.h"

/* Struct layout */
typedef struct Layout {
	char name[255];
	int rows, columns;
	int layout[MAX_ROWS][MAX_COLUMNS];
} Layout;

/* Struct Level */
typedef struct Level {
	int frame; // time
	Position camera; // camera

	/* Textures */
	Textures *textures;

	/* Map */
	MyTexture map;

	/* Player */
	int player_onload; // player onload state
	Player player; // player

	/* Tiles */ 
	int count_tiles; // count tiles
	Tile tiles[MAX_TILES]; // tiles

	/* Layout */
	int count_layouts; // count layouts
	Layout layouts[MAX_LAYOUTS]; // layouts
} Level;

/* Prototypes */

/* Initialization */
extern void level_init(Level *level, Textures *textures);

/* Create tile */ 
extern void level_create_tile(Level *level, Position pos, Color color, int collision, int type);

/* Create player */ 
extern void level_create_player(Level *level, Position pos, Color color, int speed);

/* Create map */ 
extern void level_create_map(Level *level);

/* Update */
extern void level_update(Level *level); 

/* Render */ 
extern void level_render(Level *level);

/* Create layout */
extern void create_layout(Level *level, char *name, char *path); 

/* Load layout */ 
extern Layout load_layout(char *name, char *path);

#endif