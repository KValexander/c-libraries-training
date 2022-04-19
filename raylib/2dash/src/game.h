#ifndef raylib_game_h
#define raylib_game_h

#include <raylib.h>

// Constants
#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 540
#define FPS 60

// Include files
#include "screen.h"
#include "level.h"

// Structs
typedef struct {
	int frame; // frames

	Screen screen; // struct Screen
	Levels levels; // struct Levels

	Vector2 mouse_pos; // mouse position
	
} Game;

// Prototypes
extern void game_init(Game *game);
extern void game_update(Game *game);
extern void game_render(Game *game);
extern void game_loop(Game *game);
extern void game_deinit(Game *game);

#endif