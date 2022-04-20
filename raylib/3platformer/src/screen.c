/* Include libraries */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Include libraries */
#include <raylib.h> 

/* Include files */
#include "config.h"
#include "screen.h"

/* Screen initialization */
void screen_init(Screen *screen) {

	/* Window initialization */
	InitWindow(
		get_screen_width(), // config width
		get_screen_height(), // config height
		get_screen_title() // config title
	); SetTargetFPS(get_screen_fps()); // config fps

	/* Randomizer initialization */ 
	srand(time(0));

	/* Current screen */
	screen->current_screen = SCREEN_LEVEL;

	/* Level initialization */
	level_init(&screen->level);

}

/* Update data */
void screen_update(Screen *screen) {
	screen->frame; // time

	/* Active screen */ 
	switch(screen->current_screen) {

		/* Screen select level */ 
		case SCREEN_SELECT_LEVEL: break;
		
		/* Screen level */ 
		case SCREEN_LEVEL:
		
			/* Level update */ 
			level_update(&screen->level);

		break;

		default: break;

	}

}

/* Render data */
void screen_render(Screen *screen) {
	ClearBackground(LIGHTGRAY); // backgrund

	/* Active screen */ 
	switch(screen->current_screen) {

		/* Screen select level */ 
		case SCREEN_SELECT_LEVEL: break;
		
		/* Screen level */ 
		case SCREEN_LEVEL:

			/* Level render */ 
			level_render(&screen->level);

		break;

		default: break;
		
	}

}

/* Game loop */ 
void screen_loop(Screen *screen) {

	/* Game loop */
	while(!WindowShouldClose()) {

		/* Screen update */
		screen_update(screen); 

		/* Rendering */ 
		BeginDrawing(); // start drawing

			screen_render(screen); // screen render

		EndDrawing(); // end drawing

	}

}

/* Screen deinitialization */
void screen_deinit(Screen *screen) {

	/* Level deinitialization */
	level_deinit(screen); 

	/* Close window */
	CloseWindow();

} 