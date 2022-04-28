/* Include libraries */
#include <stdio.h>

/* Include libraries */
#include <raylib.h>

/* Include files */
#include "common.h"
#include "game.h"
#include "collision.h"
#include "screens/fight.h"

/* Fight screen entry */
void fight_entry(Game *game) {

	game->battle.player[0].x = 70;
	game->battle.player[0].y = 300;

	game->battle.player[1].x = SCREEN_WIDTH - 140;
	game->battle.player[1].y = 300;
	game->battle.player[1].direction = ANIMATION_LEFT;

}

/* Fight screen update */
void fight_update(Game *game) {

	/* Update players */
	for(int i = 0; i < MAX_PLAYERS; i++) {

		/* Player update */ 
		player_update(&game->battle.player[i]);
		
		/* Character update */ 
		character_update(&game->storage.characters[game->battle.player[i].character],
						 &game->battle.player[i].is_change,
						  game->battle.player[i].state,
						  game->battle.player[i].direction,
						  game->screen_frame);

		/* Surface-Player collision */
		// collision_surface_player(game);

	}

}

/* Fight screen render */
void fight_render(Game *game) {

	/* Draw location */
	location_draw(&game->storage.locations[game->battle.selected_location]);

	/* Draw characters */
	for(int i = 0; i < game->storage.count_characters; i++)
		character_draw(&game->storage.characters[game->battle.player[i].character],
						game->battle.player[i].x, game->battle.player[i].y);

}