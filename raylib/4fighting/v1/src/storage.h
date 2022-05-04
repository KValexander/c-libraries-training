#ifndef STORAGE_H_
#define STORAGE_H_

/* Constants */
#define MAX_CHARACTERS 10
#define MAX_LOCATIONS 10

/* Include files */
#include "common.h"
#include "resources.h"
#include "storage/character.h"
#include "storage/location.h"

/* Struct Storage */
typedef struct Storage {

	/* Characters */ 
	int count_characters; // count characters
	Character characters[MAX_CHARACTERS]; // characters

	/* Locations */
	int count_locations; // count locations
	Location locations[MAX_LOCATIONS];

} Storage;

/* Prototypes */

/* Load storage */
extern void load_storage(Resources *resources, Storage *storage);

/* Create character */ 
extern void s_create_character(Storage *storage, char *name, MyTexture icon, MyTexture view, MyTexture sprite, int count_animations, Animation animations[MAX_ANIMATIONS]);

/* Get character */ 
extern Character s_get_character(Storage *storage, int index);

/* Create location */ 
extern void s_create_location(Storage *storage, char *name, float gravity, MyTexture icon, MyTexture background, int count_surfaces, Surface surfaces[MAX_SURFACES]);

/* Get location */ 
extern Location s_get_location(Storage *storage, int index);

#endif