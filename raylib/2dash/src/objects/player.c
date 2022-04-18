/* Include libraries */
#include <raylib.h>

/* Include files */
#include "game.h"
#include "player.h"

/* Player initialization */ 
void player_init(Player *player) {

	player->w = 48;
	player->h = 48;
	player->x = 0;
	player->y = 400;
	player->dx = 0.0f;
	player->dy = 0.0f;
	player->state = PLAYER_STATE_ALIVE;
	player->is_jump = 0;
	player->on_surface = 0;

}

/* Player keydown */
void player_keydown(Player *player) {

	/* Jump */
	if(IsKeyDown(KEY_UP)) {
		if(player->is_jump) {
			player->dy = -4;
			player->is_jump = 0;
		} player->dy -= 0.2f;
	}

	// if(IsKeyDown(KEY_LEFT)) // left
	// 	player->x -= 10;
	// else if(IsKeyDown(KEY_RIGHT)) // right
	// 	player->x += 10;
	// if(IsKeyDown(KEY_UP)) // up
	// 	player->y -= 10;
	// else if(IsKeyDown(KEY_DOWN)) // down
	// 	player->y += 10;

}

/* Player update */
void player_update(Player *player, float gravity, float acceleration) {

	/* Player is alive */
	if(player->state == PLAYER_STATE_ALIVE) {

		/* Player keydown */ 
		player_keydown(player);

		/* Limits */
		if(player->dx > 6)
			player->dx = 6;
		if(player->dx < 0.1f)
			player->dx = 0;

		/* Player movement */
		player->x += player->dx;
		player->y += player->dy;

		/* Check player */ 
		if(player->y > 600)
			player->state = PLAYER_STATE_DYING;

		/* Permanent impacts */
		player->dx += acceleration;
		player->dy += gravity;

	}

}

/* Player draw */ 
void player_draw(Player *player, int scroll_x, int scroll_y) {
	DrawRectangle(
		scroll_x + player->x,
		scroll_y + player->y,
		player->w,
		player->h,
		BLACK
	);
}