/* Include libraries */
#include <stdio.h>

/* Include libraries */
#include <raylib.h>

/* Include files */
#include "common.h"
#include "game.h"
#include "screens/select_character.h"

static Vector2 sc_mouse; // mouse position
static int select_character;

/* Select character screen entry */
void select_character_entry(Game *game) {

}

/* Select character screen update */
void select_character_update(Game *game) {
	
	/* Mouse position */ 
	sc_mouse = GetMousePosition();
	if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		for(int i = 0; i < game->storage.count_characters; i++) {
			if(check_collision(
				sc_mouse.x, sc_mouse.y,
				40, 100 + 84*i,
				1, 1,
				game->storage.characters[i].icon.w,
				game->storage.characters[i].icon.h
			)) select_character = i;
			else select_character = -1;
		}
	}

}

/* Select character screen render */
void select_character_render(Game *game) {

	/* Draw text */
	DrawText("Select character:", 40, 30, 36, BLACK);

	/* Drawing character selection */ 
	for(int i = 0; i < game->storage.count_characters; i++)
		DrawTexture( game->storage.characters[i].icon.texture, 40, 100 + 84*i, WHITE);

	if(select_character >= 0)
		DrawTexture( game->storage.characters[select_character].sprite.texture, SCREEN_WIDTH / 2, 0, WHITE);


}