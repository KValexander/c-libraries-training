/* Include libraries */
#include <stdio.h>
#include <string.h>

/* Include libraries */
#include <raylib.h>

/* Include files */
#include "storage/location.h"

/* Create location */
Location create_location(char *name, float gravity, MyTexture icon, MyTexture background, int count_surfaces, Surface surfaces[MAX_SURFACES]) {

	/* Create location */
	Location location;

	/* Naming */
	strcpy(location.name, name);

	/* Gravity */
	location.gravity = gravity;

	/* Textures */
	location.icon = icon;
	location.background = background;

	/* Surfaces */
	location.count_surfaces = count_surfaces;
	for(int i = 0; i < location.count_surfaces; i++)
		location.surfaces[i] = surfaces[i];

	/* Return location */
	return location;

}

/* Draw location */
void location_draw(Location *location) {

	/* Draw background */
	DrawTexture(location->background.texture,
				0, 0, WHITE);

	/* Draw surfaces */
	for(int i = 0; i < location->count_surfaces; i++)
		surface_draw(&location->surfaces[i]);

}