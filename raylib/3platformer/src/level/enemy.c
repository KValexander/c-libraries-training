/* Include libraries */
#include <stdio.h>

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
	enemy->is_dead = 0;

}

/* Enemy collision */
int enemy_collision(Enemy *enemy, int x, int y, int w, int h){
	
	/* If the enemy is dead */ 
	if(enemy->is_dead) return 0;

	/* Getting the side of the collision */
	int side = sides_collision(x, y, enemy->x, enemy->y, w, h, enemy->w, enemy->h);

	switch(side) {

		/* UP */ 
		case 1: enemy->is_dead = 1; break;

	}

	return side;
}

/* Enemy update */ 
void enemy_update(Enemy *enemy) {
	
	/* If the enemy is dead */ 
	if(enemy->is_dead) return;


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