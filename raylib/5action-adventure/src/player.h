#ifndef PLAYER_H_
#define PLAYER_H_

/* Include libraries */
#include <raylib.h>

/* Include files */
#include "common.h"
#include "tile.h"

/* Struct Player */
typedef struct Player {
	Rect rect; // x, y, w, h
	Color color; // color

	int speed; // movement speed
	Position direction; // direction

	int *count_tiles; // count tiles
	Tile *tiles; // tiles
} Player;

/* Prototypes */

/* Create player */ 
extern Player create_player(Rect rect, Color color, int speed, int *count_tiles, Tile *tiles);

/* Key down */
extern void player_key_down(Player *player);

/* Move */
extern void player_move(Player *player);

/* Update */
extern void player_update(Player *player);

/* Collision */
extern void player_collision(Player *player, int direction);

/* Draw */
extern void player_draw(Player *player, Position camera);

#endif