/* Include libraries */
#include <stdio.h>

/* Include libraries */
#include <raylib.h>

/* Include files */
#include "battle.h"

/* Battle initialization */
void battle_init(Battle *battle) {
	battle->selected_location = -1;

	/* Player initialization */
	player_init(&battle->player[0]);

}
