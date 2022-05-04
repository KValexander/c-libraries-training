/* Include libraries */
#include <stdio.h>

/* Include libraries */
#include <raylib.h>

/* Include files */
#include "common.h"
#include "game.h"
#include "screens/select_location.h"

static Vector2 sl_mouse; // mouse position

/* Select location screen entry */
void select_location_entry(Game *game) {
	game->battle.selected_location = -1; // selected location
}

/* Select location screen update */
void select_location_update(Game *game) {
	
	/* Mouse position */ 
	sl_mouse = GetMousePosition();
	if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		
		/* Go to next screen*/
		if(game->battle.selected_location >= 0)
			if(check_collision(sl_mouse.x, sl_mouse.y, SCREEN_WIDTH - 170, 30, 1, 1, 114, 40))
				return game_change_screen(game, SCREEN_FIGHT);

		/* Select character */ 
		for(int i = 0; i < game->storage.count_locations; i++) {
			if(check_collision(
				sl_mouse.x, sl_mouse.y,
				40, 100 + 164*i,
				1, 1,
				game->storage.locations[i].icon.w,
				game->storage.locations[i].icon.h
			)) {game->battle.selected_location = i; break;}
			else game->battle.selected_location = -1;
		}

	}

}

/* Select location screen render */
void select_location_render(Game *game) {

	/* Draw text */
	DrawText("Select location:", 40, 30, 36, BLACK);

	/* Drawing character selection */ 
	for(int i = 0; i < game->storage.count_locations; i++) {
		DrawTexture(game->storage.locations[i].icon.texture, 40, 100 + 164*i, WHITE);
		if(game->battle.selected_location == i)
			DrawRectangleLines(30, 90 + 164*i, 276, 164, DARKBLUE);
	}

	/* Draw selected character */ 
	if(game->battle.selected_location >= 0) {
		DrawRectangle(SCREEN_WIDTH - 170, 30, 114, 40, BLACK);
		DrawText("Next", SCREEN_WIDTH - 150, 35, 32, WHITE);
	}

}