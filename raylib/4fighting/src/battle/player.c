/* Include libraries */
#include <stdio.h>
#include <math.h>

/* Include libraries */
#include <raylib.h>

/* Include files */
#include "battle/player.h"


/* Player initialization */
void player_init(Player *player) {

	/* Selected character */ 
	player->character = -1;

	/* Data */ 
	player->x = 0;
	player->y = 0;
	player->dx = 0;
	player->dy = 0;
		
	/* States */ 
	player->state = 0;
	player->prev_state = 0;
	player->direction = 0;
	player->is_jump = 0;
	player->is_change = 0;

}

/* Player update */
void player_update(Player *player) {

	/* Check change */ 
	if(player->state != player->prev_state) {
		player->prev_state = player->state;
		player->is_change = 1;
	}

	/* KEYDOWN */ 

	/* RIGHT */
	if(IsKeyDown(KEY_RIGHT)) {
		player->state = 1;
		player->direction = 0;
		player->dx += 0.5f;
		if(player->dx > 6)
			player->dx = 6;
	}

	/* LEFT */ 
	else if(IsKeyDown(KEY_LEFT)) {
		player->state = 1;
		player->direction = 1;
		player->dx -= 0.5f;
		if(player->dx < -6)
			player->dx = -6;
	}

	/* IDLE */
	else {
		player->state = 0;
		player->dx *= 0.8f;
		if(fabsf(player->dx) < 0.1f)
			player->dx = 0;
	}

	/* DOWN */ 
	if(IsKeyDown(KEY_DOWN))
		player->state = 2;

	/* Player move */
	player->x += player->dx;
	player->y += player->dy;

}