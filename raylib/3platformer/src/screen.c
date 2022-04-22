/* Include libraries */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Include libraries */
#include <raylib.h> 

/* Include files */
#include "config.h"
#include "helpers.h"
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

	/* Level initialization */
	level_init(&screen->level);

}

/* Update data */
void screen_update(Screen *screen) {
	screen->frame; // time

	/* Select level */ 
	if(IsKeyPressed(KEY_M))
		screen->current_screen = SCREEN_SELECT_LEVEL;

	/* Active screen */ 
	switch(screen->current_screen) {

		/* Screen select level */ 
		case SCREEN_SELECT_LEVEL:
			Vector2 mouse = GetMousePosition();

			/* Select levels */ 
			for(int i = 0; i < screen->level.count_levels; i++) {
				if(collide_2d(
					20, 70*i + 20,
					mouse.x, mouse.y,
					300, 50,
					1, 1
				)) {
					DrawRectangleLines(20, 70*i + 20, 300, 50, BLACK);
					if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
						if(screen->level.levels[i].access || !i) {
							screen->current_screen = SCREEN_LEVEL;
							level_change(&screen->level, i);
						}
					}

				};

			}

		break;
		
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
		case SCREEN_SELECT_LEVEL:

			/* Out levels */
			for(int i = 0; i < screen->level.count_levels; i++) {
				char name[10]; sprintf(name, "Level %d", i + 1);
				if(!i) DrawText(name, 30, 70*i + 30, 30, BLACK);
				else DrawText(name, 30, 70*i + 30, 30, (screen->level.levels[i].access) ? BLACK : GRAY);
			}

		break;
		
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