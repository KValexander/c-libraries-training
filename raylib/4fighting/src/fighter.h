#ifndef FIGHTER_H_
#define FIGHTER_H_

/* Include libraries */
#include <raylib.h>

/* Include files */
#include "common.h"

/* Struct Health bar */
typedef struct HealthBar {
	int percents;
	float dist, unit;
	Rect bar;
} HealthBar;

/* Struct Fighter */
typedef struct Fighter {
	Rect draw_box; // draw area
	Rect attack_box; // attack area
	HealthBar health_bar; // health bar
	Position velocity; // velocity
	Color color; // color

	int countdown_attack; // countdown attack
	int countdown_attacked; // countdown attacked
	int damage; // damage
	int health; // health
	/* Control
		0 - first fighter
		1 - second fighter
	*/ int control;
	/* Direction 
		0 - right
		1 - left
	*/ int direction;

	int is_attacking; // state of attack
	int is_attacked; // state of attacked
	int is_jump; // jump state
	int is_dead; // dead state
} Fighter;

/* Prototypes */
/* Create fighter */
extern Fighter create_fighter(Rect draw_box, 	// draw box
							  Rect attack_box, 	// attack box
							  Color color, 		// collor
							  int damage,		// damage
							  int health,		// health
							  int control); 	// control

/* Attack */ 
extern void fighter_attack(Fighter *fighter);

/* Jump */ 
extern void fighter_jump(Fighter *fighter);

/* Move right */
extern void fighter_move_right(Fighter *fighter);

/* Move left */
extern void fighter_move_left(Fighter *fighter);

/* IDLE */ 
extern void fighter_move_idle(Fighter *fighter);

/* KeyDown */
extern void fighter_key_down(Fighter *fighter);

/* Update */
extern void fighter_update(Fighter *fighter);


/* Stop move */
extern void fighter_stop_move(Fighter *fighter, int x);

/* Stop falling */
extern void fighter_stop_falling(Fighter *fighter, int y);

/* Take damage */ 
extern void fighter_take_damage(Fighter *fighter, int damage);

/* Collision */
extern void fighter_collision(Fighter *fighter);

/* Dead */
extern void fighter_dead(Fighter *fighter);


/* Draw */
extern void fighter_draw(Fighter *fighter);

#endif