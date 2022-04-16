/* Include libraries */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Include libraries */
#include <raylib.h>

/* Include files */
#include "screens.h"
#include "game.h"

/* Initialization */ 
void game_init(Game *game) {

	/* Window initialization */
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Dash");
	SetTargetFPS(FPS); // FPS

	/* Randomizer initialization */ 
	srand(time(0));

	/* Screens initialization */
	game->screen = SCREEN_MAIN_MENU;
	screens_init(game);

}

/* Handling events */ 
void game_events(Game *game) {

	/* Screens events */
	screens_events(game);

}

/* Data update */ 
void game_update(Game *game) {
	game->frame++; // time

	/* Screens update */
	screens_update(game);
	
}

/* Check collisions */ 
void game_collisions(Game *game) {
	
}

/* Rendering */
void game_render(Game *game) {
	ClearBackground(SKYBLUE);

	/* Screens render */
	screens_render(game);
	
}

/* Game loop */ 
void game_loop(Game *game) {

	while(!WindowShouldClose()) {

		/* Handling events */ 
		game_events(game);

		/* Data update */ 
		game_update(game);

		/* Check collisions */ 
		game_collisions(game);

		/* Rendering */ 
		BeginDrawing();

			game_render(game);
		
		EndDrawing();

	}
}

/* Deinitialization */ 
void game_deinit(Game *game) {

	/* Close window */
	CloseWindow();

}
