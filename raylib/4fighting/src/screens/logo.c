/* Include libraries */
#include <stdio.h>

/* Include libraries */
#include <raylib.h>

/* Include files */
#include "common.h"
#include "game.h"
#include "screens/logo.h"

/* Logo screen entry */
void logo_entry(Game *game) {}

/* Logo screen update */
void logo_update(Game *game) {

	/* Timer */ 
	if(game->screen_frame > 120)
		game_change_screen(game, SCREEN_SELECT_CHARACTER);

}

/* Logo screen render */
void logo_render(Game *game) {

	/* Get texture logo */ 
	MyTexture logo = r_get_texture(&game->resources, "logo");

	/* Draw logo */
	DrawTexture(
		logo.texture,
		SCREEN_WIDTH / 2 - logo.w / 2,
		SCREEN_HEIGHT / 2 - logo.h / 2,
		WHITE
	);

}