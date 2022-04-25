/* Include libraries */
#include <stdio.h>

/* Include libraries */
#include <raylib.h>

/* Include files */
#include "common.h"
#include "game.h"

/* Screens */ 
#include "screens/logo.h"
#include "screens/select_character.h"
#include "screens/select_location.h"
#include "screens/fight.h"
#include "screens/fight_result.h"


/* Game initialization */
void game_init(Game *game) {

	/* Window initialization */
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Fighting");
	SetTargetFPS(FPS); // fps

	/* Load resources */
	load_resources(&game->resources);

	/* Load storage */
	load_storage(&game->resources, &game->storage);

	/* Battle initialization */
	battle_init(&game->battle); 

	/* Time */
	game->total_frame = 0; // total time
	game->screen_frame = 0; // screen time

	/* Current screen */ 
	// game_change_screen(game, SCREEN_LOGO);
	game_change_screen(game, SCREEN_SELECT_CHARACTER);

}

/* Game deinitialization */
void game_deinit(Game *game) {

	/* Unload resources */
	unload_resources(&game->resources);

	/* Close window */ 
	CloseWindow();
}

/* Game change screen */ 
void game_change_screen(Game *game, int screen) {

	/* In case the screen is not selected */
	int frame = game->screen_frame;

	/* Clear screen time */
	game->screen_frame = 0;

	/* Select screen */ 
	switch(screen) {

		/* Screen LOGO */ 
		case SCREEN_LOGO: logo_entry(game);
			game->c_screen = screen;
		break;

		/* Screen SELECT CHARACTER */ 
		case SCREEN_SELECT_CHARACTER: select_character_entry(game);
			game->c_screen = screen;
		break;

		/* Screen SELECT LOCATION */ 
		case SCREEN_SELECT_LOCATION: select_location_entry(game);
			game->c_screen = screen;
		break;

		/* Screen FIGHT */ 
		case SCREEN_FIGHT: fight_entry(game);
			game->c_screen = screen; 
		break;

		/* Screen FIGHT RESULT */ 
		case SCREEN_FIGHT_RESULT: fight_result_entry(game);
			game->c_screen = screen;
		break;

		/* If the screen is not selected */
		default: game->screen_frame = frame; break;

	}
}

/* Game update */ 
void game_update(Game *game) {
	game->total_frame++; // total time
	game->screen_frame++; // screen time

	/* Select screen */ 
	switch(game->c_screen) {

		/* Screen LOGO */ 
		case SCREEN_LOGO: logo_update(game);
		break;

		/* Screen SELECT CHARACTER */ 
		case SCREEN_SELECT_CHARACTER: select_character_update(game);
		break;

		/* Screen SELECT LOCATION */ 
		case SCREEN_SELECT_LOCATION: select_location_update(game);
		break;

		/* Screen FIGHT */ 
		case SCREEN_FIGHT: fight_update(game);
		break;

		/* Screen FIGHT RESULT */ 
		case SCREEN_FIGHT_RESULT: fight_result_update(game);
		break;

		/* If the screen is not selected */
		default: break;

	}

}

/* Game rendering */ 
void game_render(Game *game) {
	ClearBackground(LIGHTGRAY); // background

	/* Select screen */ 
	switch(game->c_screen) {

		/* Screen LOGO */ 
		case SCREEN_LOGO: logo_render(game);
		break;

		/* Screen SELECT CHARACTER */ 
		case SCREEN_SELECT_CHARACTER: select_character_render(game);
		break;

		/* Screen SELECT LOCATION */ 
		case SCREEN_SELECT_LOCATION: select_location_render(game);
		break;

		/* Screen FIGHT */ 
		case SCREEN_FIGHT: fight_render(game);
		break;

		/* Screen FIGHT RESULT */ 
		case SCREEN_FIGHT_RESULT: fight_result_render(game);
		break;

		/* If the screen is not selected */
		default: break;

	}

}

/* Game loop */
void game_loop(Game *game) {

	/* Game loop */
	while(!WindowShouldClose()) {

		/* Game update */
		game_update(game); 

		/* Rendering */ 
		BeginDrawing(); // start drawing

			/* Game rendering */ 
			game_render(game);

		EndDrawing(); // end drawing

	}

}