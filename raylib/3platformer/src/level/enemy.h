#ifndef ENEMY_H_
#define ENEMY_H_

/* Include libraries */
#include <raylib.h>

/* Struct Enemy */
typedef struct {
	int x, y, w, h; // char
	float dx, dy; // acc

	int is_jump; // jump
	int is_dead; // dead
} Enemy;

/* Enemy prototypes */
extern void enemy_init(Enemy *enemy); // enemy initialization
extern int enemy_collision(Enemy *enemy, int x, int y, int w, int h); // enemy collision
extern void enemy_update(Enemy *enemy); // enemy update
extern void enemy_draw(Enemy *enemy, Texture2D *texture, Vector2 camera); // enemy render

#endif