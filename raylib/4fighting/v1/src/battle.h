#ifndef BATTLE_H_
#define BATTLE_H_

/* Constants */
#define MAX_PLAYERS 2

/* Include files */
#include "storage.h"
#include "battle/player.h"

/* Struct Battle */ 
typedef struct Battle {
	int selected_location; // selected location

	Player player[MAX_PLAYERS];
} Battle;

/* Prototypes */
extern void battle_init(Battle *battle);


#endif