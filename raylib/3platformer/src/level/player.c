/* Include libraries */
#include <stdio.h>
#include <math.h>

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
	player->is_jump = 0;

}

/* Player on surface */
void player_on_surface(Player *player, int side, float x, float y, float w, float h) {
	switch(side) {
		case 1: // up
			player->dy = 0;
			player->y = y - player->h;
			player->is_jump = 1;
		break;
		case 3: // down
			if(!player->dy)
				player->dy = 0;
			player->y = y + h;
		break;
	}
}

/* Player jump */ 
void player_jump(Player *player) {
	if(player->is_jump) {
		player->dy = -10;
		player->is_jump = 0;
	} player->dy -= 0.2f;
}

/* Player update */ 
void player_update(Player *player) {

	/* JUMP */
	if(IsKeyDown(KEY_UP))
		player_jump(player);

	/* Move RIGHT */ 
	if(IsKeyDown(KEY_RIGHT)) {
		player->dx += 0.5;
		if(player->dx > 6)
			player->dx = 6;
	}

	/* Move LEFT */ 
	else if(IsKeyDown(KEY_LEFT)) {
		player->dx -= 0.5;
		if(player->dx < -6)
			player->dx = -6;
	}

	/* STOP move */
	else {
		player->dx *= 0.8f;
		if(fabsf(player->dx) < 0.1f)
			player->dx = 0;
	}

	/* Player move */
	player->x += player->dx;
	player->y += player->dy;

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