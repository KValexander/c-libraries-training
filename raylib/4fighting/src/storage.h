#ifndef STORAGE_H_
#define STORAGE_H_

/* Constants */
#define MAX_CHARACTERS 10
#define MAX_LOCATIONS 10

/* Include files */
#include "common.h"
#include "resources.h"
#include "storage/character.h"
// #include "storage/location.h"

/* Struct Storage */
typedef struct Storage {

	/* Characters */ 
	int count_characters; // count characters
	Character characters[MAX_CHARACTERS]; // characters

	/* Locations */
	int count_locations; // count locations

} Storage;

/* Prototypes */

/* Load storage */
extern void load_storage(Resources *resources, Storage *storage);

/* Create character */ 
void s_create_character(Storage *storage, char *name, MyTexture icon, MyTexture sprite, int count_animations, Animation animations[MAX_ANIMATIONS]);

#endif