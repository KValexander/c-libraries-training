#ifndef SCREEN_H_
#define SCREEN_H_

/* Include files */
#include "level.h"

/* Enum Screens*/
typedef enum {
	SCREEN_SELECT_LEVEL = 0,
	SCREEN_LEVEL
} Screens;

/* Struct Screen */ 
typedef struct {
	int frame; // time

	Level level; // struct Level
	Screens current_screen; // current screen
} Screen;

/* Prototypes */
extern void screen_init(Screen *screen); // initialization
extern void screen_update(Screen *screen); // update data
extern void screen_render(Screen *screen); // render data
extern void screen_loop(Screen *screen); // game loop
extern void screen_deinit(Screen *screen); // deinitialization

#endif