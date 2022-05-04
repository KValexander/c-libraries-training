#ifndef GAME_H_
#define GAME_H_

/* Constants */
#define NUM_FIGHTERS 2

/* Include libraries */
#include <raylib.h>

/* Include files */
#include "common.h"
#include "fighter.h"

/* Struct Game */
typedef struct Game {
	int frame; // time
	Fighter fighters[NUM_FIGHTERS];
} Game;

/* Prototypes */
/* Game initialization */
extern void game_init(Game *game);

/* Create fighters */
extern void create_fighters(Game *game);

/* Game update */
extern void game_update(Game *game);

/* Game collisions */
extern void game_collisions(Game *game);

/* Game render */
extern void game_render(Game *game);

/* Game loop */
extern void game_loop(Game *game);

/* Game deinitialization */
extern void game_deinit(Game *game); 

#endif