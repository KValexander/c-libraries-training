/* Include libraries */
#include <stdio.h>

/* Include libraries */
#include <raylib.h>

/* Include files */
#include "common.h"
#include "game.h"
#include "screens/logo.h"

/* Intro initialization */ 
static LogoIntro logo_intro;

/* Logo screen entry */
void logo_entry(Game *game) {

	logo_intro.w = 267;
	logo_intro.h = 225;
	logo_intro.line_frame = 0;
	logo_intro.current_frame = 0;
	logo_intro.max_lines = 17;
	logo_intro.max_on_line = 17;

}

/* Logo screen update */
void logo_update(Game *game) {

	/* Update animation */ 
	if(game->screen_frame % 2 == 0) {
		logo_intro.current_frame++;
		if(logo_intro.current_frame >= logo_intro.max_on_line) {
			logo_intro.current_frame = 0;
			logo_intro.line_frame++;
		}
		if(logo_intro.line_frame >= logo_intro.max_lines)
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
			logo_intro.w*logo_intro.current_frame,
			logo_intro.h*logo_intro.line_frame,
			logo_intro.w,
			logo_intro.h
		},
		(Vector2) {
			SCREEN_WIDTH / 2 - logo_intro.w / 2,
			SCREEN_HEIGHT / 2 - logo_intro.h / 2
		},
		WHITE
	);

}