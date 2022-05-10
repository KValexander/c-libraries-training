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

	/* Status
		0 - UP,
		1 - RIGHT,
		2 - DOWN,
		3 - LEFT
	*/
	player.status = 0; 

	/* Onload texture */
	player.onload_texture = 0;

	/* Animation state */
	player.animation_state = 0;

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

/* Give texture */
void player_give_texture(Player *player, MyTexture texture, int animation_state) {
	
	/* Texture */ 
	player->texture = texture;
	
	/* Onload texture state */ 
	player->onload_texture = 1;

	/* Animation state */
	player->animation_state = animation_state;

	/* Animation */
	if(player->animation_state) {

		/* Number of animation frames */
		player->animation.x = 3;
		player->animation.y = 3;

		/* Current frame */
		player->frame.x = 0; // x
		player->frame.y = 0; // y

		/* Single frame size */ 
		player->frame.w = player->rect.w;
		player->frame.h = player->rect.h;


	/* Player size */ 
	} else {
		player->rect.w = player->texture.w;
		player->rect.h = player->texture.h;
	}
	
}

/* Set status */
void player_set_status(Player *player, int status) {
	switch(status) {

		/* UP */
		case 0:
			player->status = 0;
			player->frame.y = 3;
		break;

		/* RIGHT */
		case 1:
			player->status = 1;
			player->frame.y = 2;
		break;

		/* DOWN */
		case 2:
			player->status = 2;
			player->frame.y = 0;
		break;

		/* LEFT */
		case 3:
			player->status = 3;
			player->frame.y = 1;
		break;

	}
} 

/* Key down */
void player_key_down(Player *player) {

	/* VERTICAL */
	/* DOWN */
	if (IsKeyDown(KEY_DOWN)) {
		player->direction.y = 1;
		player_set_status(player, 2);
	}

	/* UP */ 
	else if(IsKeyDown(KEY_UP)) {
		player->direction.y = -1;
		player_set_status(player, 0);
	}

	/* STOP */ 
	else player->direction.y = 0;


	/* HORIZONTAL */ 
	/* RIGHT */
	if(IsKeyDown(KEY_RIGHT)) {
		player->direction.x = 1;
		player_set_status(player, 1);
	}

	/* LEFT */ 
	else if(IsKeyDown(KEY_LEFT)) {
		player->direction.x = -1;
		player_set_status(player, 3);
	}

	/* STOP */ 
	else player->direction.x = 0;

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
		if(collide(player->rect.x, player->rect.y, player->tiles[i].hitbox.x, player->tiles[i].hitbox.y, player->rect.w, player->rect.h, player->tiles[i].hitbox.w, player->tiles[i].hitbox.h )) {

			/* Direction */ 
			switch(direction) {

				/* HORIZONTAL */ 
				case 0:

					/* RIGHT */ 
					if(player->direction.x > 0)
						player->rect.x -= player->speed;

					/* LEFT */ 
					else if(player->direction.x < 0)
						player->rect.x += player->speed;

				break;

				/* VERTICAL */
				case 1:

					/* TOP */ 
					if(player->direction.y < 0)
						player->rect.y += player->speed;

					/* BOTTOM */ 
					else if(player->direction.y > 0)
						player->rect.y -= player->speed;

				break;

			}

		}

	}

}


/* Update */
void player_update(Player *player, int time) {

	/* Key down */
	player_key_down(player);

	/* Player animation */
	player_animation(player, time);

	/* Move */
	player_move(player);

}

/* Animation */
void player_animation(Player *player, int time) {
	if(!player->direction.x && !player->direction.y)
		player->frame.x = 1;
	else if(time % 10 == 0)
		player->frame.x = (player->frame.x >= player->animation.x - 1) ? 0 : ++player->frame.x;
} 

/* Draw */
void player_draw(Player *player, Position camera) {

	/* Onload texture */
	if(player->onload_texture) {

		/* Draw part of the texture */ 
		if(player->animation_state)
			DrawTextureRec(
				player->texture.texture,
				(Rectangle) {
					player->frame.w * player->frame.x,
					player->frame.h * player->frame.y,
					player->frame.w,
					player->frame.h
				},
				(Vector2) {
					camera.x + player->rect.x,
					camera.y + player->rect.y,
				},
				WHITE
			);

		/* Draw texture */
		else DrawTexture(
				player->texture.texture,
				camera.x + player->rect.x,
				camera.y + player->rect.y,
				WHITE
			);
	}

	/* Draw rectangle */
	else DrawRectangle(
			camera.x + player->rect.x,
			camera.y + player->rect.y,
			player->rect.w,
			player->rect.h,
			player->color
		);

	/* Draw hitbox */
	DrawRectangleLines(
		camera.x + player->rect.x,
		camera.y + player->rect.y,
		player->rect.w,
		player->rect.h,
		RED
	);
}