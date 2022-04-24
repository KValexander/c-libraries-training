/* Include libraries */
#include <stdio.h>
#include <string.h>

/* Include libraries */
#include <raylib.h>

/* Include files */
#include "storage.h"

/* Load storage */
void load_storage(Resources *resources, Storage *storage) {
	/* Helpers */
	Frame frames[MAX_FRAMES];
	int pw = 0, ph = 0;

	/* Load characters */

	/* Load texture */
	MyTexture aya_texture = r_get_texture(resources, "character_aya");

	/* Create frames */
	/* IDLE */
	frames[0] = create_frame(pw, ph, 0, 0, 57, 103, 16, 8, 41, 95);
	pw += 57;


}

/* create character */
void s_create_character(Storage *storage) {

}

/* Get character */
void s_get_character(Storage *storage, char *name) {

}