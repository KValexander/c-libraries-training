/* Include libraries */
#include <stdio.h>

/* Include libraries */
#include <raylib.h>

/* Include files */
#include "common.h"
#include "game.h"
#include "screens/select_character.h"

static Vector2 sc_mouse; // mouse position

/* Select character screen entry */
void select_character_entry(Game *game) {
	game->battle.player[0].character = -1; // selected character
	game->battle.player[1].character = -1; // selected character
}

/* Select character screen update */
void select_character_update(Game *game) {
	
	/* Mouse position */ 
	sc_mouse = GetMousePosition();
	if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		
		/* Go to next screen*/
		if(game->battle.player[0].character >= 0) {
			if(check_collision(sc_mouse.x, sc_mouse.y, SCREEN_WIDTH - 170, 30, 1, 1, 114, 40)) {
				game->battle.player[1].character = !game->battle.player[0].character;
				return game_change_screen(game, SCREEN_FIGHT);
			}
		}


		/* Select character */ 
		for(int i = 0; i < game->storage.count_characters; i++) {
			if(check_collision(
				sc_mouse.x, sc_mouse.y,
				40, 100 + 84*i,
				1, 1,
				game->storage.characters[i].icon.w,
				game->storage.characters[i].icon.h
			)) game->battle.player[0].character = i;
			else game->battle.player[0].character = -1;
		}
	}

}

/* Select character screen render */
void select_character_render(Game *game) {

	/* Draw text */
	DrawText("Select character:", 40, 30, 36, BLACK);

	/* Drawing character selection */ 
	for(int i = 0; i < game->storage.count_characters; i++) {
		DrawTexture(game->storage.characters[i].icon.texture, 40, 100 + 84*i, WHITE);
		if(game->battle.player[0].character == i)
			DrawRectangleLines(30, 90 + 84*i, 68, 68, DARKBLUE);
	}

	/* Draw selected character */ 
	if(game->battle.player[0].character >= 0) {
		DrawTexture(game->storage.characters[game->battle.player[0].character].view.texture, 200, 100, WHITE);
		DrawRectangle(SCREEN_WIDTH - 170, 30, 114, 40, BLACK);
		DrawText("Next", SCREEN_WIDTH - 150, 35, 32, WHITE);
	}

}