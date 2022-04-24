#ifndef CHARACTER_H_
#define CHARACTER_H_

/* Constants */
#define MAX_ANIMATIONS 10 

/* Include files */
#include "storage/animation.h"

/* Struct Character */ 
typedef struct Character {
	char name[255]; // character name
	
	float x, y; // position
	float dx, dy; // acc

	int direction; // direction
	int is_jump; // is jump

	/* Animations */
	int count_animations; // count_animations
	Animation animations[MAX_ANIMATIONS]; // animations

} Character;

/* Prototypes */
extern Character create_character(); // load character
extern void c_create_animation(Character *character); // load animation

#endif