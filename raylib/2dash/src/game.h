#ifndef raylib_game_h
#define raylib_game_h

// Constants
#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 540
#define FPS 60

// Include files
#include "screen.h"
#include "assets.h"
#include "level.h"

// Structs
typedef struct {
	int frame; // frames

	Screen screen; // struct Screen
	Assets assets; // struct Assets
	Levels levels; // struct Levels
	
} Game;

// Prototypes
extern void game_init(Game *game);
extern void game_update(Game *game);
extern void game_render(Game *game);
extern void game_loop(Game *game);
extern void game_deinit(Game *game);

#endif