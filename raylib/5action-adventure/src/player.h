#ifndef PLAYER_H_
#define PLAYER_H_

/* Include libraries */
#include <raylib.h>

/* Include files */
#include "common.h"
#include "textures.h"
#include "tile.h"

/* Struct Player */
typedef struct Player {
	Rect rect; // x, y, w, h
	Color color; // color
	int status; // status

	int onload_texture; // onload texture
	MyTexture texture; // texture

	int animation_state; // animation state
	Position animation; // animation
	Rect frame; // frame

	int speed; // movement speed
	Position direction; // direction

	int *count_tiles; // count tiles
	Tile *tiles; // tiles

	int current_side; // collision current side
	int previous_side; // collision previous side
} Player;

/* Prototypes */

/* Create player */ 
extern Player create_player(Rect rect, Color color, int speed, int *count_tiles, Tile *tiles);

/* Give texture */
extern void player_give_texture(Player *player, MyTexture texture, int animation_state);

/* Set status */
extern void player_set_status(Player *player, int status);

/* Key down */
extern void player_key_down(Player *player);

/* Move */
extern void player_move(Player *player);

/* Update */
extern void player_update(Player *player, int time);

/* Collision */
extern void player_collision(Player *player, int direction);

/* Animation */
extern void player_animation(Player *player, int time);

/* Draw */
extern void player_draw(Player *player, Position camera);

#endif