#ifndef PLAYER_H_
#define PLAYER_H_

/* Include libraries */
#include <raylib.h>

/* Struct Player */
typedef struct {
	float x, y, w, h; // char
	float dx, dy; // acc

	int direction; // direction
	int line_frame; // line frame
	int current_frame; // current frame

	int is_jump; // jump
} Player;

/* Player prototypes */
extern void player_init(Player *player); // player initialization

extern void player_on_surface(Player *player, int side, float x, float y, float w, float h); // player on surface

extern void player_jump(Player *player); // player jump
extern void player_move_right(Player *player, int time); // player move right
extern void player_move_left(Player *player, int time); // player move left
extern void player_idle(Player *player); // player idle

extern void player_update(Player *player, int time); // player update
extern void player_draw(Player *player, Texture2D *texture, Vector2 camera); // player render

#endif