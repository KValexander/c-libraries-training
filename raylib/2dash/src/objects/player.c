/* Include libraries */
#include <raylib.h>

/* Include files */
#include "game.h"
#include "player.h"

/* Player initialization */ 
void player_init(Player *player) {

	player->w = 48;
	player->h = 48;
	player->x = WINDOW_WIDTH / 2 - 16;
	player->y = WINDOW_HEIGHT / 2 - 16;
	player->dx = 0.0f;
	player->dy = 0.0f;
	player->state = PLAYER_STATE_ALIVE;
	player->is_jump = 0.0f;
	player->on_surface = 0.0f;

}

/* Player events */
void player_events(Player *player) {

	if(IsKeyDown(KEY_LEFT)) // left
		player->x -= 10;
	if(IsKeyDown(KEY_RIGHT)) // right
		player->x += 10;
	if(IsKeyDown(KEY_UP)) // up
		player->y -= 10;
	if(IsKeyDown(KEY_DOWN)) // down
		player->y += 10;

}

/* Player render */ 
void player_render(Player *player) {

	DrawRectangle(
		player->x,
		player->y,
		player->w,
		player->h,
		WHITE
	);

}