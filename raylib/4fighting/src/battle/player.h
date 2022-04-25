#ifndef PLAYER_H_
#define PLAYER_H_

/* Struct Player */ 
typedef struct Player {
	int character; // selected character

	float x, y; // position
	int dx, dy; // acceleration

	int direction; // direction
	int is_jump; // is jump
} Player;

#endif