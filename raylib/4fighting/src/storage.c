/* Include libraries */
#include <stdio.h>
#include <string.h>

/* Include libraries */
#include <raylib.h>

/* Include files */
#include "storage.h"

/* Load storage */
void load_storage(Resources *resources, Storage *storage) {
	/* Counts */
	storage->count_characters = 0; // count characters
	storage->count_locations = 0; // count locations

	/* Helpers */
	MyTexture my_sprite;
	MyTexture my_icon;
	Frame frames[MAX_FRAMES];
	Animation animations[MAX_ANIMATIONS];
	int pw = 0, ph = 0;

	/* Load characters */

	/* Load textures */
	my_sprite = r_get_texture(resources, "character_aya");
	my_icon = r_get_texture(resources, "icon_aya");

	/* IDLE */
	/* Create frames */
	frames[0] = create_frame(pw, ph, 0, 0, 57, 103, 16, 8, 41, 95); pw += 57;
	frames[1] = create_frame(pw, ph, 0, 0, 57, 103, 15, 8, 42, 95); pw += 57;
	frames[2] = create_frame(pw, ph, 0, 0, 58, 103, 14, 8, 40, 95); pw += 58;
	frames[3] = create_frame(pw, ph, 0, 0, 58, 103, 12, 8, 46, 95); pw += 58;
	frames[4] = create_frame(pw, ph, 0, 0, 60, 103, 13, 8, 44, 95); pw += 60;
	frames[5] = create_frame(pw, ph, 0, 0, 60, 103, 14, 8, 42, 95); pw += 60;
	frames[6] = create_frame(pw, ph, 0, 0, 58, 103, 10, 8, 44, 95); pw += 58;
	frames[7] = create_frame(pw, ph, 0, 0, 58, 103, 16, 8, 40, 95); pw = 0;
	/* Create animation */
	animations[0] = create_animation("idle", 10, 8, frames, 8, 40);

	/* MOVE */
	/* Create frames */
	frames[0] = create_frame(pw, ph, 0, 0, 54, 102, 16, 8, 32, 94); pw += 54;
	frames[1] = create_frame(pw, ph, 0, 0, 63, 102, 18, 8, 32, 94); pw += 63;
	frames[2] = create_frame(pw, ph, 0, 0, 68, 102, 19, 8, 32, 94); pw += 68;
	frames[3] = create_frame(pw, ph, 0, 0, 57, 102, 15, 8, 34, 94); pw += 57;
	frames[4] = create_frame(pw, ph, 0, 0, 53, 102, 14, 8, 32, 94); pw += 53;
	frames[5] = create_frame(pw, ph, 0, 0, 62, 102, 13, 8, 40, 94); pw += 32;
	frames[6] = create_frame(pw, ph, 0, 0, 69, 102, 19, 8, 40, 94); pw += 69;
	frames[7] = create_frame(pw, ph, 0, 0, 55, 102, 14, 8, 32, 94); pw = 0;
	/* Create animation */
	animations[1] = create_animation("move", 10, 8, frames, 8, 224);

	/* Create character */
	s_create_character(storage, "aya", my_icon, my_sprite, 2, animations);

}

/* create character */
void s_create_character(Storage *storage, char *name, MyTexture icon, MyTexture sprite, int count_animations, Animation animations[MAX_ANIMATIONS]) {
	storage->characters[storage->count_characters++] = create_character(name, icon, sprite, count_animations, animations);
}

/* Get character */
void s_get_character(Storage *storage, char *name) {

}