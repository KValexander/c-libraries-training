/* Include libraries */
#include <stdio.h>

/* Include libraries */
#include <raylib.h>

/* Include files */
#include "common.h"
#include "game.h"
#include "screens/fight.h"

/* Fight screen entry */
void fight_entry(Game *game) {

	game->battle.player[0].x = 30;
	game->battle.player[0].y = 300;

}

/* Fight screen update */
void fight_update(Game *game) {

	/* Player update */
	player_update(&game->battle.player[0]);

	/* Character update */
	character_update(&game->storage.characters[game->battle.player[0].character],
					 &game->battle.player[0], game->screen_frame); 

}

/* Fight screen render */
void fight_render(Game *game) {

	/* Character draw */
	character_draw(&game->storage.characters[game->battle.player[0].character],
					game->battle.player[0].x, game->battle.player[0].y);

}