/* Include libraries */
#include <stdio.h>

/* Include files */
#include "player.h"

/* Create player */
Player create_player(Rect rect, Color color, int speed, int *count_tiles, Tile *tiles) {

	/* Create player */
	Player player;

	/* Rect */
	player.rect = rect;

	/* Color */
	player.color = color; 

	/* Speed */
	player.speed = speed;

	/* Direction
		x: 0 - stop, -1 - left, 1 - right
		y: 0 - stop, -1 - down, 1 - up
	*/ 
	player.direction.x = 0;
	player.direction.y = 0;

	/* Tiles */
	player.count_tiles = count_tiles;
	player.tiles = tiles;

	/* Collision side */
	player.current_side = 0;
	player.previous_side = 0;

	/* Return player */
	return player;

}

/* Key down */
void player_key_down(Player *player) {

	/* HORIZONTAL */ 
	/* RIGHT */
	if(IsKeyDown(KEY_RIGHT))
		player->direction.x = 1;

	/* LEFT */ 
	else if(IsKeyDown(KEY_LEFT))
		player->direction.x = -1;

	/* STOP */ 
	else player->direction.x = 0;
	

	/* VERTICAL */
	/* DOWN */
	if (IsKeyDown(KEY_DOWN))
		player->direction.y = 1;

	/* UP */ 
	else if(IsKeyDown(KEY_UP))
		player->direction.y = -1;

	/* STOP */ 
	else player->direction.y = 0;

}

/* Move */
void player_move(Player *player) {

	/* HORIZONTAL */ 
	player->rect.x += player->direction.x * player->speed;
	player_collision(player, 0); // horizontal collision

	/* VERTICAL */
	player->rect.y += player->direction.y * player->speed;
	player_collision(player, 1); // vertical collision

}

/* Collision */
void player_collision(Player *player, int direction) {

	/* Collision with tiles */
	for(int i = 0; i < *player->count_tiles; i++) {
		/* Checking the collision state of a tile */
		if(!player->tiles[i].collision) return;

		/* Check collide with tile */ 
		if(collide(player->rect.x, player->rect.y, player->tiles[i].rect.x, player->tiles[i].rect.y, player->rect.w, player->rect.h, player->tiles[i].rect.w, player->tiles[i].rect.h )) {

			/* Direction */ 
			switch(direction) {

				/* HORIZONTAL */ 
				case 0:

					/* RIGHT */ 
					if(player->direction.x > 0)
						player->rect.x = player->rect.x - player->speed;

					/* LEFT */ 
					else if(player->direction.x < 0)
						player->rect.x = player->rect.x + player->speed;

				break;

				/* VERTICAL */
				case 1:

					/* TOP */ 
					if(player->direction.y < 0)
						player->rect.y = player->rect.y + player->speed;

					/* BOTTOM */ 
					else if(player->direction.y > 0)
						player->rect.y = player->rect.y - player->speed;

				break;

			}

		}

	}
	
}


/* Update */
void player_update(Player *player) {

	/* Key down */
	player_key_down(player);

	/* Move */
	player_move(player);

}

/* Draw */
void player_draw(Player *player, Position camera) {
	DrawRectangle(
		camera.x + player->rect.x,
		camera.y + player->rect.y,
		player->rect.w,
		player->rect.h,
		player->color
	);
}