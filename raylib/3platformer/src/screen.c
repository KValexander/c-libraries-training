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
	screen->current_screen = SCREEN_SELECT_LEVEL;

	change_config_prop("WIDTH", "560");

}

/* Update data */
void screen_update(Screen *screen) {

}

/* Render data */
void screen_render(Screen *screen) {

}

/* Game loop */ 
void screen_loop(Screen *screen) {

	/* Game loop */
	while(!WindowShouldClose()) {

		/* Drawing */ 
		BeginDrawing(); // start drawing

			ClearBackground(LIGHTGRAY); // backgrund

		EndDrawing(); // end drawing

	}

}

/* Screen deinitialization */
void screen_deinit(Screen *screen) {

	/* Close window */
	CloseWindow();

} 