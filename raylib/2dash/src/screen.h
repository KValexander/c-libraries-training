#ifndef raylib_screen_h
#define raylib_screen_h

// Enum Current
typedef enum {
	SCREEN_MAIN_MENU = 0,
	SCREEN_SELECT_LEVEL,
	SCREEN_LEVEL,
	SCREEN_LEVEL_WIN,
	SCREEN_LEVEL_GAMEOVER
} Current;

// Struct Screen
typedef struct {
	Current current;
} Screen;

// Prototypes
extern void screen_init(Screen* screen);
extern void screen_change(Screen* screen, int n);
extern int screen_check(int n);

// extern void screens_init(Game *game);
// extern void screens_events(Game *game);
// extern void screens_update(Game *game);
// extern void screens_render(Game *game);

#endif