/* Include libraries */
#include <stdio.h>

/* Include libraries */
#include <raylib.h>

/* Include files */
#include "level/player.h"

/* Player initialization */ 
void player_init(Player *player) {

	player->x = 0;
	player->y = 0;
	player->w = 46;
	player->h = 84;
	player->dx = 0.0f;
	player->dy = 0.0f;

}

/* Player update */ 
void player_update(Player *player) {

	/* KeyDown */
	if(IsKeyDown(KEY_RIGHT)) // right
		player->x += 10;
	else if (IsKeyDown(KEY_LEFT)) // left
		player->x -= 10;
	if (IsKeyDown(KEY_UP)) // up
		player->y -= 10;
	else if (IsKeyDown(KEY_DOWN)) // down
		player->y += 10;

}

/* Player render */ 
void player_draw(Player *player, Texture2D *texture, Vector2 camera) {
	DrawTexture(
		*texture,
		camera.x + player->x,
		camera.y + player->y,
		WHITE
	);
}