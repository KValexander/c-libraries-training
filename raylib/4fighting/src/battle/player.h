#ifndef PLAYER_H_
#define PLAYER_H_

/* Include files */
#include "common.h"

/* Struct Player */ 
typedef struct Player {
	int character; // selected character

	float x, y; // position
	float dx, dy; // acceleration

	AnimationState state; // animation state
	AnimationState prev_state; // previous animation state
	AnimationDirection direction; // direction

	int control; // player control

	int is_jump; // is jump
	int is_change; // is change
} Player;

/* Prototypes */
extern void player_init(Player *player, int control);

// extern void player_down(Player *player);
// extern void player_jump(Player *player);
// extern void player_move_right(Player *player);
// extern void player_move_left(Player *player);
// extern void player_attack(Player *player);

extern void player_update(Player *player); 

extern void player_ai(Player *player);

#endif