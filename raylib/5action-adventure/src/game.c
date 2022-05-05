/* Include libraries */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Include files */
#include "game.h"

/* Game init */
void game_init(Game *game) {

	/* Window initialization */
	InitWindow(WIDTH, HEIGHT, "Simple action-adventure");
	/* Set target FPS */
	SetTargetFPS(FPS);

	/* Randomizer initialization */
	srand(time(0));

	/* Level initialization */
	level_init(&game->level);

}

/* Game update */
void game_update(Game *game) {
	game->frame; // time

	/* Level update */
	level_update(&game->level);

}

/* Game render */
void game_render(Game *game) {
	ClearBackground(DARKGRAY); // background

	/* Level render */
	level_render(&game->level);

}

/* Game loop */
void game_loop(Game *game) {

	/* Game loop */ 
	while(!WindowShouldClose()) {

		/* Game update */
		game_update(game);

		/* Rendering */
		BeginDrawing(); // start draw

			game_render(game); // drawing
		
		EndDrawing(); // end draw

	}

}

/* Game deinitialization */
void game_deinit(Game *game) {

	/* Close window */
	CloseWindow();

}