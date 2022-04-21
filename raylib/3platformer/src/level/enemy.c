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
	enemy->w = 46;
	enemy->h = 84;
	enemy->dx = 0.0f;
	enemy->dy = 0.0f;
	enemy->is_jump = 0;
	enemy->is_dead = 0;

}

/* Enemy jump */ 
void enemy_jump(Enemy *enemy) {
	if(enemy->is_jump) {
		enemy->dy = -10;
		enemy->is_jump = 0;
	} enemy->dy -= 0.2f;
}

/* Enemy update */ 
void enemy_update(Enemy *enemy) {
	
	/* If the enemy is dead */ 
	if(enemy->is_dead) return;

	/* Enemy move */
	enemy->x += enemy->dx;
	enemy->y += enemy->dy;

}

/* Enemy render */ 
void enemy_draw(Enemy *enemy, Texture2D *texture, Vector2 camera) {
	
	/* If the enemy is not dead */ 
	if(!enemy->is_dead)

		/* Draw texture */ 
		DrawTexture(
			*texture,
			camera.x + enemy->x,
			camera.y + enemy->y,
			WHITE
		);
}