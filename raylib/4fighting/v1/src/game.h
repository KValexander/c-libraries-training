#ifndef GAME_H_
#define GAME_H_

/* Constants */
#define MAX_CHARACTERS 10
#define MAX_LOCATIONS 10

/* Include files */
#include "resources.h"
#include "storage.h"
#include "battle.h"

/* Enum GameScreen */
typedef enum GameScreen{
	SCREEN_LOGO = 0,
	SCREEN_SELECT_CHARACTER,
	SCREEN_SELECT_LOCATION,
	SCREEN_FIGHT,
	SCREEN_FIGHT_RESULT
} GameScreen;

/* Struct Game */
typedef struct Game {
	int total_frame; // total time
	int screen_frame; // screen time
	GameScreen c_screen; // current screen

	Resources resources; // struct Resources
	Storage storage; // struct storage
	Battle battle; // struct Battle
} Game;

/* Prototypes */

/* Initialization and deinitialization */ 
extern void game_init(Game *game); // game initialization
extern void game_deinit(Game *Game); // game deinitialization

/* Working with screens */
extern void game_change_screen(Game *game, int screen); // change screen

/* Process */ 
extern void game_update(Game *game); // game update
extern void game_render(Game *game); // game render
extern void game_loop(Game *game); 	 // game loop


#endif