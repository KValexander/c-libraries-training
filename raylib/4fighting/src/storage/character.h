#ifndef CHARACTER_H_
#define CHARACTER_H_

/* Constants */
#define MAX_ANIMATIONS 10 

/* Include files */
#include "storage/animation.h"

/* Struct Character */ 
typedef struct Character {

	char name[255]; // character name

	/* Animations */
	int count_animations; // count_animations
	Animation animations[MAX_ANIMATIONS]; // animations

} Character;

#endif