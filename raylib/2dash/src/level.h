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
	Player player;
	Rect rects[MAX_RECTS];
} Level;

// Struct Levels
typedef struct {
	Level levels[MAX_LEVELS];
} Levels;

// Prototypes
extern void level_init();
extern void level_load();
extern void level_update();
extern void level_render();
extern void level_deinit();

#endif