#ifndef raylib_game_h
#define raylib_game_h

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 540
#define FPS 60

typedef struct {
	int frame;
} Game;

extern void game_init(Game *game);
extern void game_events(Game *game);
extern void game_update(Game *game);
extern void game_collisions(Game *game);
extern void game_render(Game *game);
extern void game_loop(Game *game);
extern void game_deinit(Game *game);

#endif