#ifndef GAME_H_
#define GAME_H_

/* Include libraries */
#include <raylib.h>

/* Include files */
#include "common.h"
#include "textures.h"
#include "level.h"

/* Struct Game */
typedef struct Game {
	int frame; // time
	
	Textures textures; // struct Textures
	Level level; // struct Level
} Game;

/* Prototypes */
/* Game initialization */
extern void game_init(Game *game);

/* Game update */
extern void game_update(Game *game);

/* Game render */
extern void game_render(Game *game);

/* Game loop */
extern void game_loop(Game *game);

/* Game deinitialization */
extern void game_deinit(Game *game); 

#endif