#ifndef PLAYER_H_
#define PLAYER_H_

/* Struct Player */ 
typedef struct Player {
	int character; // selected character

	float x, y; // position
	float dx, dy; // acceleration

	int state; // state
	int prev_state; // previous state
	int direction; // direction
	int is_jump; // is jump
	int is_change; // is change
} Player;

/* Prototypes */
extern void player_init(Player *player);

// extern void player_down(Player *player);
// extern void player_jump(Player *player);
// extern void player_move_right(Player *player);
// extern void player_move_left(Player *player);
// extern void player_attack(Player *player);

extern void player_update(Player *player); 

#endif