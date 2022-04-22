#ifndef ENEMY_H_
#define ENEMY_H_

/* Include libraries */
#include <raylib.h>

/* Struct Enemy */
typedef struct {
	float x, y, w, h; // char
	float dx, dy; // acc

	int direction; // direction
	int line_frame; // line frame
	int current_frame; // current frame

	int is_jump; // jump
	int is_dead; // dead
} Enemy;

/* Enemy prototypes */
extern void enemy_init(Enemy *enemy); // enemy initialization

extern void enemy_jump(Enemy *enemy); // enemy jump
extern void enemy_move_right(Enemy *enemy, int time); // enemy move right
extern void enemy_move_left(Enemy *enemy, int time); // enemy move left
extern void enemy_idle(Enemy *enemy); // enemy idle

extern void enemy_ai(Enemy *enemy, int time); // enemy AI

extern void enemy_update(Enemy *enemy, int time); // enemy update
extern void enemy_draw(Enemy *enemy, Texture2D *texture, Vector2 camera); // enemy render

#endif