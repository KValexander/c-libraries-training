#ifndef raylib_level_h
#define raylib_level_h

// Constants
#define MAX_LEVELS 10
#define MAX_RECTS 1000
#define GRAVITY 0.4f

// Include files
#include "objects/player.h"

// Struct Position
typedef struct {
	int x, y;
} Position;

// Struct Rect
typedef struct {
	int x, y, w, h;
} Rect;

// Struct Level
typedef struct {
	char name[30]; // level name
	int difficulty; // level difficulty
	int count_rects; // count rects
	int state; // level state

	Position camera; // struct Position, camera
	Player player; // struct Player
	Rect rects[MAX_RECTS]; // array of Rects
} Level;

// Struct Levels
typedef struct {
	int current_level; // current level
	int count_levels; // number of existing levels
	
	Level levels[MAX_LEVELS]; // levels
} Levels;

// Prototypes
extern void level_init(Levels *levels);
extern void level_loading(Levels *levels);
extern void level_change(Levels *levels, int n);

extern void level_update(Levels *levels);
extern void level_render(Levels *levels);

#endif