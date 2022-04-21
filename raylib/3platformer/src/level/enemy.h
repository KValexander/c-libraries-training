#ifndef ENEMY_H_
#define ENEMY_H_

/* Include libraries */
#include <raylib.h>

/* Struct Enemy */
typedef struct {
	float x, y, w, h; // char
	float dx, dy; // acc

	int is_jump; // jump
	int is_dead; // dead
} Enemy;

/* Enemy prototypes */
extern void enemy_init(Enemy *enemy); // enemy initialization
extern void enemy_on_surface(Enemy *enemy, int side, float x, float y, float w, float h); // enemy on surface
extern int enemy_collision(Enemy *enemy, float x, float y, float w, float h); // enemy collision
extern void enemy_update(Enemy *enemy); // enemy update
extern void enemy_draw(Enemy *enemy, Texture2D *texture, Vector2 camera); // enemy render

#endif