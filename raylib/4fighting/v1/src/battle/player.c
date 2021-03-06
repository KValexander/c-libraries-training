/* Include libraries */
#include <stdio.h>
#include <math.h>

/* Include libraries */
#include <raylib.h>

/* Include files */
#include "battle/player.h"


/* Player initialization */
void player_init(Player *player, int control) {

	/* Selected character */ 
	player->character = 0;

	/* Data */ 
	player->x = 0;
	player->y = 0;
	player->dx = 0;
	player->dy = 0;

	/* Control */
	player->control = control;
		
	/* States */ 
	player->state = ANIMATION_IDLE;
	player->prev_state = ANIMATION_IDLE;
	player->direction = ANIMATION_RIGHT;
	player->prev_direction = ANIMATION_RIGHT;
	player->is_jump = 0;
	player->is_change = 0;

}

/* Player update */
void player_update(Player *player) {

	/* Check change */ 
	if(player->direction != player->prev_direction || player->state != player->prev_state) {
		player->prev_direction = player->direction;
		player->prev_state = player->state;
		player->is_change = 1;
	}


	/* KEYDOWN */ 
	if(player->control) {

		/* RIGHT */
		if(IsKeyDown(KEY_RIGHT)) {
			player->state = ANIMATION_MOVE;
			player->direction = ANIMATION_RIGHT;
			player->dx += 0.5f;
			if(player->dx > 6)
				player->dx = 6;
		}

		/* LEFT */ 
		else if(IsKeyDown(KEY_LEFT)) {
			player->state = ANIMATION_MOVE;
			player->direction = ANIMATION_LEFT;
			player->dx -= 0.5f;
			if(player->dx < -6)
				player->dx = -6;
		}

		/* IDLE */
		else {
			player->state = ANIMATION_IDLE;
			player->dx *= 0.8f;
			if(fabsf(player->dx) < 0.1f)
				player->dx = 0;
		}

		/* DOWN */ 
		if(IsKeyDown(KEY_DOWN))
			player->state = ANIMATION_DOWN;

	/* Player AI */ 
	} else player_ai(player);

	/* Player move */
	player->x += player->dx;
	player->y += player->dy;

	/* Player state */
	// player->state = player->state + player->direction; 

}

/* Player AI */
void player_ai(Player *player) {

} 