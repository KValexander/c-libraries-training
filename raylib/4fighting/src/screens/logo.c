/* Include libraries */
#include <stdio.h>

/* Include libraries */
#include <raylib.h>

/* Include files */
#include "common.h"
#include "game.h"
#include "screens/logo.h"

/* Intro initialization */ 
static Intro intro;

/* Logo screen entry */
void logo_entry(Game *game) {

	intro.w = 267;
	intro.h = 225;
	intro.line_frame = 0;
	intro.current_frame = 0;
	intro.max_lines = 17;
	intro.max_on_line = 17;

}

/* Logo screen update */
void logo_update(Game *game) {

	/* Update animation */ 
	if(game->screen_frame % 2 == 0) {
		intro.current_frame++;
		if(intro.current_frame >= intro.max_on_line) {
			intro.current_frame = 0;
			intro.line_frame++;
		}
		if(intro.line_frame >= intro.max_lines)
			return game_change_screen(game, SCREEN_SELECT_CHARACTER);
	}
}

/* Logo screen render */
void logo_render(Game *game) {
	ClearBackground(BLACK); // background

	/* Get texture intro */ 
	MyTexture my_texture = r_get_texture(&game->resources, "intro");

	/* Drawing part of the texture */ 
	DrawTextureRec(
		my_texture.texture,
		(Rectangle) {
			intro.w*intro.current_frame,
			intro.h*intro.line_frame,
			intro.w,
			intro.h
		},
		(Vector2) {
			SCREEN_WIDTH / 2 - intro.w / 2,
			SCREEN_HEIGHT / 2 - intro.h / 2
		},
		WHITE
	);

}