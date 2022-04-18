#ifndef raylib_level_h
#define raylib_level_h

// Constants
#define MAX_LEVELS 10
#define MAX_RECTS 1000
#define LEVEL_GRAVITY 0.4f
#define LEVEL_ACCELERATION 0.5f

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
	int frame; // time
	int difficulty; // level difficulty
	int count_rects; // count rects
	char name[30]; // level name

	int is_victory; // victory

	Position camera; // struct Position, camera
	Position start_player; // struct Position, start player pos
	Player player; // struct Player
	Rect victory_condition; // struct Rect, victory condition
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
extern void level_one_init(Level *level);
extern void level_loading(Levels *levels);
extern void level_change(Levels *levels, int n);

extern void level_update(Levels *levels);
extern void level_collisions(Levels *levels);
extern void level_render(Levels *levels);

#endif