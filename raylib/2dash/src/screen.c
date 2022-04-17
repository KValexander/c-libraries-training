/* Include files */
#include "screen.h"

/* Screen initialization */ 
void screen_init(Screen *screen) {
	screen->current = SCREEN_SELECT_LEVEL;
}

/* Change screen */
void screen_change(Screen *screen, int n) {
	if(screen_check(n))
		screen->current = n;
}

/* Check screen */
int screen_check(int n) {
	switch(n) {
		case SCREEN_SELECT_LEVEL:
		case SCREEN_LEVEL:
		case SCREEN_LEVEL_WIN:
		case SCREEN_LEVEL_GAMEOVER:
			return 1;
		break;
		default: return 0; break;
	}
}

// /* Screens init */
// void screen_init(Game *game) {

// 	/* Screens */
// 	switch(game->screen) {

// 		/* Main menu */
// 		case SCREEN_MAIN_MENU: break;
		
// 		/* Select game */
// 		case SCREEN_SELECT_LEVEL: break;
		
// 		/* Game */
// 		case SCREEN_LEVEL: break;
		
// 		/* Win */
// 		case SCREEN_LEVEL_WIN: break;
		
// 		/* Gameover */
// 		case SCREEN_LEVEL_GAMEOVER: break;
		
// 		default: break;
// 	}

// }