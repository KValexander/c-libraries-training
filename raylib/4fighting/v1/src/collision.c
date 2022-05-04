/* Include libraries */
#include <stdio.h>

/* Include libraries */
#include <raylib.h>

/* Include files */
#include "collision.h"

/* Collision Surface-Player */
void collision_surface_player(Game *game) {
	
	Location location = s_get_location(&game->storage, game->battle.selected_location);

	for(int i = 0; i < MAX_PLAYERS; i++) {

		Character character = s_get_character(&game->storage, game->battle.player[i].character);
		Animation animation = get_current_animation(&character);
		Frame frame = get_current_frame(&animation);

		for(int j = 0; j < game->storage.locations[game->battle.selected_location].count_surfaces; i++) {

			if(check_collision(
				game->battle.player[i].x,
				game->battle.player[i].y,
				location.surfaces[j].x,
				location.surfaces[j].y,
				frame.display.w,
				frame.display.h,
				location.surfaces[j].w,
				location.surfaces[j].h
			)) game->battle.player[i].dy = 0;

		}

	}

}