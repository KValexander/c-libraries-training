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

	/* Level initialization */
	level_init(&game->levels);

}

/* Data update */ 
void game_update(Game *game) {
	game->frame++; // time
	
}

/* Rendering */
void game_render(Game *game) {
	ClearBackground(SKYBLUE); // backgrund
	
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
