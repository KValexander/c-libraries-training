#ifndef STORAGE_H_
#define STORAGE_H_

/* Constants */
#define MAX_CHARACTERS 10
#define MAX_LOCATIONS 10

/* Include files */
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

#endif