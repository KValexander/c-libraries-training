/* Include libraries */
#include <stdio.h>

/* Include libraries */
#include <raylib.h>

/* Include files */
#include "config.h"
#include "helpers.h"
#include "level/background.h"

/* Background initialization */ 
void background_init(Background *background) {

	/* Main background */ 
	background[0].w = get_screen_width(); // width
	background[0].h = get_screen_height(); // height
	background[0].scroll = 0.0f; // scroll
	background[0].scroll_speed = 0.1f; // scroll speed
	load_texture(
		&background[0].image,
		"assets/background.png",
		background[0].w,
		background[0].h
	); // load texture

	// Cloud background
	background[1].w = 1920; // width
	background[1].h = 1018; // height
	background[1].scroll = 0.0f; // scroll
	background[1].scroll_speed = 0.5f; // scroll speed
	load_texture(
		&background[1].image,
		"assets/cloud.png",
		background[1].w,
		background[1].h
	); // load texture

}

/* Background deinitialization */
void background_deinit(Background *background) {
	for(int i = 0; i < NUM_BACKGROUNDS; i++)
		UnloadTexture(background[i].image);
}

/* Background update */
void background_update(Background *background) {

	/* Scroll update */
	background[0].scroll -= background[0].scroll_speed;
	background[1].scroll -= background[1].scroll_speed;

	/* Check scroll */
	if(background[0].scroll <= -background[0].w) background[0].scroll = 0;
	if(background[1].scroll <= -background[1].w) background[1].scroll = 0;

}

/* Background draw */
void background_draw(Background *background) {

	/* Background draw */
	for(int i = 0; i < NUM_BACKGROUNDS; i++) {
		DrawTextureEx(
			background[i].image, // texture
			(Vector2){ background[i].scroll, 0}, // pos
			0.0f, // rotate
			1.0f, // scale
			WHITE // color
		);
		DrawTextureEx(
			background[i].image, // texture
			(Vector2){ background[i].w + background[i].scroll, 0}, // pos
			0.0f, // rotate
			1.0f, // scale
			WHITE // color
		);
	}

} 