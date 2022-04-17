#ifndef raylib_level_h
#define raylib_level_h

// Constants
#define MAX_LEVELS 10
#define MAX_RECTS 1000

// Include files
#include "objects/player.h"

// Struct Rect
typedef struct {
	int x, y, w, h;
} Rect;

// Struct Level
typedef struct {
	int difficulty; // level difficulty
	Player player; // struct Player
	Rect rects[MAX_RECTS]; // array of Rects
} Level;

// Struct Levels
typedef struct {
	int current; // current level
	
	Level levels[MAX_LEVELS]; // levels
} Levels;

// Prototypes
extern void level_init(Levels *levels);
extern void level_loading(Levels *levels);
extern void level_select(Levels *levels, int current);
extern void level_update(Levels *levels);
extern void level_render(Levels *levels);

#endif