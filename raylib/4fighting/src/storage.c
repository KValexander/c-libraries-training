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
	MyTexture my_icon;
	MyTexture my_view;
	MyTexture my_sprite;
	Frame frames[MAX_FRAMES];
	Animation animations[MAX_ANIMATIONS];
	int pw = 0, ph = 0;

	/* Load character AYA */
	/* Load textures */
	my_icon = r_get_texture(resources, "aya_icon");
	my_view = r_get_texture(resources, "aya_view");
	my_sprite = r_get_texture(resources, "aya_sprite");

	/* IDLE */
	/* Create frames */
	frames[0] = create_frame(pw, ph, 0, 0, 57, 103, 16, 8, 41, 95); pw += 57;
	frames[1] = create_frame(pw, ph, 0, 0, 57, 103, 15, 8, 42, 95); pw += 57;
	frames[2] = create_frame(pw, ph, 0, 0, 58, 103, 14, 8, 40, 95); pw += 58;
	frames[3] = create_frame(pw, ph, 0, 0, 58, 103, 12, 8, 46, 95); pw += 58;
	frames[4] = create_frame(pw, ph, 0, 0, 60, 103, 13, 8, 44, 95); pw += 60;
	frames[5] = create_frame(pw, ph, 0, 0, 58, 103, 14, 8, 42, 95); pw += 58;
	frames[6] = create_frame(pw, ph, 0, 0, 60, 103, 10, 8, 44, 95); pw += 60;
	frames[7] = create_frame(pw, ph, 0, 0, 58, 103, 16, 8, 40, 95); pw = 0;
	/* Create animation */
	animations[0] = create_animation("idle", 5, 8, frames, 8, 40);

	/* MOVE */
	/* Create frames */
	frames[0] = create_frame(pw, ph, 0, 0, 54, 102, 16, 8, 32, 94); pw += 54;
	frames[1] = create_frame(pw, ph, 0, 0, 63, 102, 18, 8, 32, 94); pw += 63;
	frames[2] = create_frame(pw, ph, 0, 0, 68, 102, 19, 8, 32, 94); pw += 68;
	frames[3] = create_frame(pw, ph, 0, 0, 57, 102, 15, 8, 34, 94); pw += 57;
	frames[4] = create_frame(pw, ph, 0, 0, 53, 102, 14, 8, 32, 94); pw += 53;
	frames[5] = create_frame(pw, ph, 0, 0, 62, 102, 13, 8, 40, 94); pw += 62;
	frames[6] = create_frame(pw, ph, 0, 0, 69, 102, 19, 8, 40, 94); pw += 69;
	frames[7] = create_frame(pw, ph, 0, 0, 55, 102, 14, 8, 32, 94); pw = 0;
	/* Create animation */
	animations[2] = create_animation("move", 5, 8, frames, 8, 224);

	/* Create character AYA */
	s_create_character(storage, "aya", my_icon, my_view, my_sprite, 2, animations);

	/* Load character SAKUYA */
	my_icon = r_get_texture(resources, "sakuya_icon");
	my_view = r_get_texture(resources, "sakuya_view");
	my_sprite = r_get_texture(resources, "sakuya_sprite");

	/* IDLE */
	/* Create frames */
	frames[0] = create_frame(pw, ph, 0, 0, 54, 97, 0, 0, 0, 0); pw += 54;
	frames[1] = create_frame(pw, ph, 0, 0, 54, 97, 0, 0, 0, 0); pw += 54;
	frames[2] = create_frame(pw, ph, 0, 0, 53, 97, 0, 0, 0, 0); pw += 53;
	frames[3] = create_frame(pw, ph, 0, 0, 54, 97, 0, 0, 0, 0); pw += 54;
	frames[4] = create_frame(pw, ph, 0, 0, 53, 97, 0, 0, 0, 0); pw += 53;
	frames[5] = create_frame(pw, ph, 0, 0, 53, 97, 0, 0, 0, 0); pw = 0;
	/* Create animation */
	animations[0] = create_animation("idle", 7, 6, frames, 8, 40);

	/* IDLE BACK */
	/* Create frames */
	frames[0] = create_frame(pw, ph, 0, 0, 54, 97, 0, 0, 0, 0); pw += 54;
	frames[1] = create_frame(pw, ph, 0, 0, 54, 97, 0, 0, 0, 0); pw += 54;
	frames[2] = create_frame(pw, ph, 0, 0, 53, 97, 0, 0, 0, 0); pw += 53;
	frames[3] = create_frame(pw, ph, 0, 0, 54, 97, 0, 0, 0, 0); pw += 54;
	frames[4] = create_frame(pw, ph, 0, 0, 53, 97, 0, 0, 0, 0); pw += 53;
	frames[5] = create_frame(pw, ph, 0, 0, 53, 97, 0, 0, 0, 0); pw = 0;
	/* Create animation */
	animations[1] = create_animation("idle", 7, 6, frames, 8, 40);

	/* MOVE */
	/* Create frames */
	frames[0] = create_frame(pw, ph, 0, 0, 48, 98, 0, 0, 0, 0); pw += 48;
	frames[1] = create_frame(pw, ph, 0, 0, 49, 98, 0, 0, 0, 0); pw += 49;
	frames[2] = create_frame(pw, ph, 0, 0, 46, 98, 0, 0, 0, 0); pw += 46;
	frames[3] = create_frame(pw, ph, 0, 0, 49, 98, 0, 0, 0, 0); pw += 49;
	frames[4] = create_frame(pw, ph, 0, 0, 51, 98, 0, 0, 0, 0); pw += 51;
	frames[5] = create_frame(pw, ph, 0, 0, 50, 98, 0, 0, 0, 0); pw += 50;
	frames[6] = create_frame(pw, ph, 0, 0, 48, 98, 0, 0, 0, 0); pw += 48;
	frames[7] = create_frame(pw, ph, 0, 0, 48, 98, 0, 0, 0, 0); pw += 48;
	frames[8] = create_frame(pw, ph, 0, 0, 47, 98, 0, 0, 0, 0); pw = 0;
	/* Create animation */
	animations[2] = create_animation("move", 5, 9, frames, 8, 224);

	/* MOVE BACK */
	/* Create frames */
	frames[0] = create_frame(pw, ph, 0, 0, 48, 98, 0, 0, 0, 0); pw += 48;
	frames[1] = create_frame(pw, ph, 0, 0, 46, 98, 0, 0, 0, 0); pw += 46;
	frames[2] = create_frame(pw, ph, 0, 0, 46, 98, 0, 0, 0, 0); pw += 46;
	frames[3] = create_frame(pw, ph, 0, 0, 49, 98, 0, 0, 0, 0); pw += 49;
	frames[4] = create_frame(pw, ph, 0, 0, 51, 98, 0, 0, 0, 0); pw += 51;
	frames[5] = create_frame(pw, ph, 0, 0, 50, 98, 0, 0, 0, 0); pw += 50;
	frames[6] = create_frame(pw, ph, 0, 0, 48, 98, 0, 0, 0, 0); pw += 48;
	frames[7] = create_frame(pw, ph, 0, 0, 48, 98, 0, 0, 0, 0); pw += 48;
	frames[8] = create_frame(pw, ph, 0, 0, 49, 98, 0, 0, 0, 0); pw = 0;
	/* Create animation */
	animations[3] = create_animation("move_back", 5, 9, frames, 508, 224);

	/* Create character SAKUYA */
	s_create_character(storage, "sakuya", my_icon, my_view, my_sprite, 2, animations);


}

/* create character */
void s_create_character(Storage *storage, char *name, MyTexture icon, MyTexture view, MyTexture sprite, int count_animations, Animation animations[MAX_ANIMATIONS]) {
	storage->characters[storage->count_characters++] = create_character(name, icon, view, sprite, count_animations, animations);
}

/* Get character */
Character s_get_character(Storage *storage, int index) {
	for(int i = 0; i < storage->count_characters; i++)
		if(i == index) return storage->characters[i];
}