#ifndef LOCATION_H_
#define LOCATION_H_

/* Constants */
#define MAX_SURFACES 10

/* Include files */
#include "common.h"
#include "storage/surface.h"
#include "resources/texture.h"

/* Struct Location */
typedef struct Location {
	char name[255]; // location name
	float gravity; // gravity

	int count_surfaces; // count surfaces
	Surface surfaces[MAX_SURFACES]; // surfaces

	MyTexture icon; // icon
	MyTexture background; // background
} Location;

/* Prototypes */
/* Create location */ 
extern Location create_location(char *name, float gravity, MyTexture icon, MyTexture background, int count_surfaces, Surface surfaces[MAX_SURFACES]);

/* Draw location */
extern void location_draw(Location *location);

#endif