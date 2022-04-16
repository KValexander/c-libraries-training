#ifndef raylib_game_h
#define raylib_game_h

// Constants
#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 540
#define FPS 60

// Include files
#include "assets.h"
#include "level.h"

// Enum Screens
typedef enum {
	SCREEN_MAIN_MENU = 0,
	SCREEN_SELECT_GAME,
	SCREEN_GAME,
	SCREEN_WIN,
	SCREEN_GAMEOVER
} Screens;

// Structs
typedef struct {
	int frame; // frames

	Levels levels; // struct Levels
	Assets assets; // struct Assets
	
	Screens screen; // enum Screens
} Game;

// Prototypes
extern void game_init(Game *game);
extern void game_events(Game *game);
extern void game_update(Game *game);
extern void game_collisions(Game *game);
extern void game_render(Game *game);
extern void game_loop(Game *game);
extern void game_deinit(Game *game);

#endif