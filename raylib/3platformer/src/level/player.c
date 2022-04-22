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
	player->w = 64;
	player->h = 116;
	player->dx = 0.0f;
	player->dy = 0.0f;
	player->is_jump = 0;
	player->direction = 0;
	player->line_frame = 0;
	player->current_frame = 0;

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

/* Player move right */
void player_move_right(Player *player, int time) {
	player->direction = 0; // right direction
	player->line_frame = 2; // line frame
	if(time % 10 == 0) player->current_frame = (player->current_frame > 2) ? 0 : ++player->current_frame; // current frame
	player->dx += 0.5;
	if(player->dx > 6)
		player->dx = 6;
}

/* Player move left */
void player_move_left(Player *player, int time) {
	player->direction = 1; // left direction
	player->line_frame = 1; // line frame
	if(time % 10 == 0) player->current_frame = (player->current_frame > 2) ? 0 : ++player->current_frame; // current frame
	player->dx -= 0.5;
	if(player->dx < -6)
		player->dx = -6;
}

/* Player idle */
void player_idle(Player *player) {
	player->line_frame = 0; // line frame
	player->current_frame = !player->direction; // current frame
	player->dx *= 0.8f;
	if(fabsf(player->dx) < 0.1f)
		player->dx = 0;
}

/* Player update */ 
void player_update(Player *player, int time) {

	/* JUMP */
	if(IsKeyDown(KEY_UP))
		player_jump(player);

	/* Move RIGHT */ 
	if(IsKeyDown(KEY_RIGHT))
		player_move_right(player, time);

	/* Move LEFT */ 
	else if(IsKeyDown(KEY_LEFT))
		player_move_left(player, time);

	/* STOP move */
	else player_idle(player);

	/* Jump animation */
	if(player->dy != 0) {
		player->line_frame = 0; // line frame
		player->current_frame = (player->direction) ? 2 : 3; // current_frame
	}

	/* Player move */
	player->x += player->dx;
	player->y += player->dy;

}

/* Player render */ 
void player_draw(Player *player, Texture2D *texture, Vector2 camera) {

	/* Drawing part of the texture */ 
	DrawTextureRec(
		*texture,
		(Rectangle) {
			player->w*player->current_frame,
			player->h*player->line_frame,
			player->w,
			player->h
		},
		(Vector2) {
			camera.x + player->x,
			camera.y + player->y
		},
		WHITE
	);

	/* Draw rectangle lines */
	/* HITBOX */ 
	DrawRectangleLines(
		camera.x + player->x + player->w / 4,
		camera.y + player->y + player->h / 4,
		player->w / 2,
		player->h / 2,
		MAROON
	);

}