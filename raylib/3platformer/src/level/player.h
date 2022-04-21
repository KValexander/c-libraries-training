#ifndef PLAYER_H_
#define PLAYER_H_

/* Include libraries */
#include <raylib.h>

/* Struct Player */
typedef struct {
	int x, y, w, h; // char
	float dx, dy; // acc

	int is_jump; // jump
} Player;

/* Player prototypes */
extern void player_init(Player *player); // player initialization
extern void player_update(Player *player); // player update
extern void player_draw(Player *player, Texture2D *texture, Vector2 camera); // player render

#endif