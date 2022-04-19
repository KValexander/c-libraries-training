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

	/* Level initialization */
	level_init(&game->levels);
	level_change(&game->levels, 0);

	/* Screen initialization */
	screen_init(&game->screen);
	screen_change(&game->screen, SCREEN_SELECT_LEVEL);

}

/* Data update */ 
void game_update(Game *game) {
	game->frame++; // time

	/* To select level */
	if(IsKeyDown(KEY_M))
		screen_change(&game->screen, SCREEN_SELECT_LEVEL);

	/* Screens */
	switch(game->screen.current) {

		/* Select game */
		case SCREEN_SELECT_LEVEL:

			/* Mouse position */ 
			game->mouse_pos = GetMousePosition();

			/* Mouse interaction with levels */ 
			for(int i = 0; i <= game->levels.count_levels; i++) {
				// DrawRectangleLines(20, 70*i + 20, 300, 50, BLACK);
				if(collide_2d(
					20, 70*i + 20,
					game->mouse_pos.x, game->mouse_pos.y,
					300, 50,
					1, 1
				)) {
					DrawRectangleLines(20, 70*i + 20, 300, 50, BLACK);
					if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
						screen_change(&game->screen, SCREEN_LEVEL);
						level_change(&game->levels, i);
					}

				};
			}

		break;
		
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
	ClearBackground(LIGHTGRAY); // backgrund

	/* Screens */
	switch(game->screen.current) {

		/* Select game */
		case SCREEN_SELECT_LEVEL:

			/* Drawing game levels */
			for(int i = 0; i <= game->levels.count_levels; i++) {
				// DrawRectangleLines(20, 70*i + 20, 300, 50, BLACK);
				DrawText(game->levels.levels[i].name, 30, 70*i + 30, 30, BLACK);
			}

		break;
		
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
