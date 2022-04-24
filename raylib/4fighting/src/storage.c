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
	Frame frames[8];
	int pw = 0, ph = 0;

	/* Load characters */

	/* Load texture */
	MyTexture aya_texture = r_get_texture(resources, "character_aya");

	/* Create frames */
	/* IDLE */
	frames[0] = s_create_frame(pw, ph, 0, 0, 57, 103, 16, 8, 41, 95);

	// frame_display = {0, 0, 57, 103};
	// frame_hitbox = {16, 8, 41, 95};
	// Frame idle_second = create_frame(frame_display, frame_hitbox);

	// Animation idle = create_animation(
	// 	create_frame(frame_display, frame_hitbox)
	// );

	// /* Animations start position */
	// int anim_start[2][2];

	// /* IDLE */
	// anim_start[0][0] = 8; // x
	// anim_start[0][1] = 40; // y

	// /* Move */
	// anim_start[1][0] = 8; // x
	// anim_start[1][1] = 224; // y


	// /* Animations */ 
	// int animations[2][8][6];

	// /* IDLE */
	// /* First frame */ 
	// int animations[0][0][0] = 57; // display_w
	// int animations[0][0][1] = 103; // display_h
	// int animations[0][0][2] = 41; // hitbox_x
	// int animations[0][0][3] = 95; // hitbox_h
	// int animations[0][0][4] = 16; // hitbox_start_x
	// int animations[0][0][5] = 8; // hitbox_start_y
	// /* Second frame */ 
	// int animations[0][1][0] = 57; // display_w
	// int animations[0][1][1] = 103; // display_h
	// int animations[0][1][2] = 42; // hitbox_x
	// int animations[0][1][3] = 95; // hitbox_h
	// int animations[0][1][4] = 15; // hitbox_start_x
	// int animations[0][1][5] = 8; // hitbox_start_y
	// /* Third frame */ 
	// int animations[0][2][0] = 58; // display_w
	// int animations[0][2][1] = 103; // display_h
	// int animations[0][2][2] = 40; // hitbox_x
	// int animations[0][2][3] = 95; // hitbox_h
	// int animations[0][2][4] = 14; // hitbox_start_x
	// int animations[0][2][5] = 8; // hitbox_start_y
	// /* Fourth frame */ 
	// int animations[0][2][0] = 58; // display_w
	// int animations[0][2][1] = 103; // display_h
	// int animations[0][2][2] = 40; // hitbox_x
	// int animations[0][2][3] = 95; // hitbox_h
	// int animations[0][2][4] = 14; // hitbox_start_x
	// int animations[0][2][5] = 8; // hitbox_start_y
	// /* Fifth frame */ 
	// int animations[0][2][0] = 58; // display_w
	// int animations[0][2][1] = 103; // display_h
	// int animations[0][2][2] = 40; // hitbox_x
	// int animations[0][2][3] = 95; // hitbox_h
	// int animations[0][2][4] = 14; // hitbox_start_x
	// int animations[0][2][5] = 8; // hitbox_start_y
	// /* Sixth frame */ 
	// int animations[0][2][0] = 58; // display_w
	// int animations[0][2][1] = 103; // display_h
	// int animations[0][2][2] = 40; // hitbox_x
	// int animations[0][2][3] = 95; // hitbox_h
	// int animations[0][2][4] = 14; // hitbox_start_x
	// int animations[0][2][5] = 8; // hitbox_start_y
	// /* Seventh frame */ 
	// int animations[0][2][0] = 58; // display_w
	// int animations[0][2][1] = 103; // display_h
	// int animations[0][2][2] = 40; // hitbox_x
	// int animations[0][2][3] = 95; // hitbox_h
	// int animations[0][2][4] = 14; // hitbox_start_x
	// int animations[0][2][5] = 8; // hitbox_start_y
	// /* Eight frame */ 
	// int animations[0][2][0] = 58; // display_w
	// int animations[0][2][1] = 103; // display_h
	// int animations[0][2][2] = 40; // hitbox_x
	// int animations[0][2][3] = 95; // hitbox_h
	// int animations[0][2][4] = 14; // hitbox_start_x
	// int animations[0][2][5] = 8; // hitbox_start_y


}
	
/* Create frame */
Frame s_create_frame(int pw, int ph, int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
	Rect frame_display = {pw + x1, ph + y1, w1, h1};
	Rect frame_hitbox = {x2, h2, w2, h2};
	Frame frame = create_frame(frame_display, frame_hitbox);
	return frame;
}


/* create character */
void s_create_character(Storage *storage) {

}

/* Get character */
void s_get_character(Storage *storage, char *name) {

}