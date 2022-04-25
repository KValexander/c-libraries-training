#ifndef CHARACTER_H_
#define CHARACTER_H_

/* Constants */
#define MAX_ANIMATIONS 10

/* Include libraries */
#include <raylib.h>

/* Include files */
#include "resources/texture.h"
#include "storage/animation.h"
#include "battle/player.h"

/* Struct Character */ 
typedef struct Character {
	char name[255]; // character name

	/* Textures */
	MyTexture sprite;
	MyTexture icon;

	/* Animations */
	int count_animations; // count_animations
	int current_animation; // current animation
	Animation animations[MAX_ANIMATIONS]; // animations

} Character;

/* Prototypes */

/* Create character */ 
extern Character create_character(char *name, MyTexture icon, MyTexture sprite, int count_animations, Animation animations[MAX_ANIMATIONS]);

/* Change animation */
extern void character_change_animation(Character *character, int change);

/* Character update */ 
extern void character_update(Character *character, Player *player, int time);

/* Character draw */
extern void character_draw(Character *character, int x, int y);

#endif