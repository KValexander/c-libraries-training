#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <raylib.h>

#include "game.h"

/* Initialization */ 
void game_init(Game *game) {

	/* Window initialization */
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Dash");
	SetTargetFPS(FPS); // FPS

}

/* Handling events */ 
void game_events(Game *game) {

}

/* Data update */ 
void game_update(Game *game) {
	
}

/* Check collisions */ 
void game_collisions(Game *game) {
	
}

/* Rendering */
void game_render(Game *game) {
	ClearBackground(SKYBLUE);
	
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
