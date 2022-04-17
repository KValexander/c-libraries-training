/* Include libraries */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Include libraries */
#include <raylib.h>

/* Include files */
#include "game.h"

/* Initialization */
void game_init(Game *game) {

	/* Window initialization */
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Dash");
	SetTargetFPS(FPS); // FPS

	/* Randomizer initialization */ 
	srand(time(0));

	/* Screen initialization */
	screen_init(&game->screen);
	screen_change(&game->screen, SCREEN_LEVEL);

	/* Level initialization */
	level_init(&game->levels);
	level_change(&game->levels, 0);

}

/* Data update */ 
void game_update(Game *game) {
	game->frame++; // time

	/* Screens */
	switch(game->screen.current) {

		/* Select game */
		case SCREEN_SELECT_LEVEL: break;
		
		/* Level */
		case SCREEN_LEVEL:

			/* Update level */
			level_update(&game->levels);

		break;
		
		/* Win */
		case SCREEN_LEVEL_WIN: break;
		
		/* Gameover */
		case SCREEN_LEVEL_GAMEOVER: break;
		
		default: break;
	}
	
}

/* Rendering */
void game_render(Game *game) {
	ClearBackground(WHITE); // backgrund

	/* Screens */
	switch(game->screen.current) {

		/* Select game */
		case SCREEN_SELECT_LEVEL: break;
		
		/* Level */
		case SCREEN_LEVEL:

			/* Render level */
			level_render(&game->levels);

		break;
		
		/* Win */
		case SCREEN_LEVEL_WIN: break;
		
		/* Gameover */
		case SCREEN_LEVEL_GAMEOVER: break;
		
		default: break;
	}
	
}

/* Game loop */ 
void game_loop(Game *game) {

	/* Game loop */ 
	while(!WindowShouldClose()) {

		/* Data update */ 
		game_update(game);

		/* Rendering */ 
		BeginDrawing(); // start drawing

			game_render(game); // drawing
		
		EndDrawing(); // end drawing

	}
}

/* Deinitialization */ 
void game_deinit(Game *game) {

	/* Close window */
	CloseWindow();

}
