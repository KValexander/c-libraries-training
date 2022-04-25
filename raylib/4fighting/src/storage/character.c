/* Include libraries */
#include <stdio.h>
#include <string.h>

/* Include libraries */
#include <raylib.h>

/* Include files */
#include "storage/character.h"


/* Create character */
Character create_character(char *name, MyTexture icon, MyTexture sprite, int count_animations, Animation animations[MAX_ANIMATIONS]) {

	/* Create character */ 
	Character character;

	/* Naming */ 
	strcpy(character.name, name);

	/* Textures */
	character.icon = icon;
	character.sprite = sprite;

	/* Animations */
	character.count_animations = count_animations;
	for(int i = 0; i < character.count_animations; i++)
		character.animations[i] = animations[i];

	/* Return character */
	return character;

}