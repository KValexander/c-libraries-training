/* Include libraries */
#include <stdio.h>
#include <math.h>

/* Include libraries */
#include <raylib.h>

/* Include files */
#include "helpers.h"
#include "level/enemy.h"

/* Enemy initialization */ 
void enemy_init(Enemy *enemy) {

	enemy->x = 0;
	enemy->y = 0;
	enemy->w = 66;
	enemy->h = 120;
	enemy->dx = 0.0f;
	enemy->dy = 0.0f;
	enemy->is_jump = 0;
	enemy->is_dead = 0;
	enemy->direction = 0;
	enemy->line_frame = 0;
	enemy->current_frame = 0;

}

/* Enemy jump */ 
void enemy_jump(Enemy *enemy) {
	if(enemy->is_jump) {
		enemy->dy = -10;
		enemy->is_jump = 0;
	} enemy->dy -= 0.2f;
}

/* Enemy move right */
void enemy_move_right(Enemy *enemy, int time) {
	enemy->direction = 0; // right direction
	enemy->line_frame = 2; // line frame
	if(time % 10 == 0) enemy->current_frame = (enemy->current_frame > 3) ? 0 : ++enemy->current_frame; // current frame
	enemy->dx += 0.5;
	if(enemy->dx > 6)
		enemy->dx = 6;
}

/* Enemy move left */
void enemy_move_left(Enemy *enemy, int time) {
	enemy->direction = 1; // left direction
	enemy->line_frame = 1; // line frame
	if(time % 10 == 0) enemy->current_frame = (enemy->current_frame > 3) ? 0 : ++enemy->current_frame; // current frame
	enemy->dx -= 0.5;
	if(enemy->dx < -6)
		enemy->dx = -6;
}

/* Enemy idle */
void enemy_idle(Enemy *enemy) {
	enemy->line_frame = 0; // line frame
	enemy->current_frame = !enemy->direction; // current frame
	enemy->dx *= 0.8f;
	if(fabsf(enemy->dx) < 0.1f)
		enemy->dx = 0;
}

/* Enemy AI */
void enemy_ai(Enemy *enemy, int time) {

	if(enemy->dy != 0 && enemy->is_jump) {
		enemy->dx = (enemy->direction) ? 6 : -6;
		enemy->direction = !enemy->direction;
	}

	if(enemy->dy == 0 && time % 10 == 0)
		(enemy->direction) ? enemy_move_left(enemy, time) : enemy_move_right(enemy, time);

}

/* Enemy update */ 
void enemy_update(Enemy *enemy, int time) {
	
	/* If the enemy is dead */ 
	if(enemy->is_dead) return;

	/* Enemy AI */ 
	enemy_ai(enemy, time);

	// /* JUMP */
	// if(IsKeyDown(KEY_W))
	// 	enemy_jump(enemy);

	// /* Move RIGHT */ 
	// if(IsKeyDown(KEY_D))
	// 	enemy_move_right(enemy, time);

	// /* Move LEFT */ 
	// else if(IsKeyDown(KEY_A))
	// 	enemy_move_left(enemy, time);

	// /* STOP move */
	// else enemy_idle(enemy);

	/* Jump animation */
	if(enemy->dy != 0) {
		enemy->line_frame = 0; // line frame
		enemy->current_frame = (enemy->direction) ? 2 : 3; // current_frame
	}

	/* Enemy move */
	enemy->x += enemy->dx;
	enemy->y += enemy->dy;

}

/* Enemy render */ 
void enemy_draw(Enemy *enemy, Texture2D *texture, Vector2 camera) {
	
	/* If the enemy is not dead */ 
	if(!enemy->is_dead) {

		/* Drawing part of the texture */ 
		DrawTextureRec(
			*texture,
			(Rectangle) {
				enemy->w*enemy->current_frame,
				enemy->h*enemy->line_frame,
				enemy->w,
				enemy->h
			},
			(Vector2) {
				camera.x + enemy->x,
				camera.y + enemy->y
			},
			WHITE
		);

		/* Draw rectangle lines */
		/* HITBOX */ 
		DrawRectangleLines(
			camera.x + enemy->x + enemy->w / 4,
			camera.y + enemy->y + enemy->h / 4,
			enemy->w / 2,
			enemy->h / 2,
			DARKGREEN
		);

	}
}