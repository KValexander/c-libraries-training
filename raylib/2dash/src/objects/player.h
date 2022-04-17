#ifndef raylib_player_h
#define raylib_player_h

// Struct Player state
typedef enum {
	PLAYER_STATE_ALIVE = 0,
	PLAYER_STATE_DYING
} PlayerState;

// Struct Player
typedef struct {
	int x, y, w, h; // pos, size
	float dx, dy; // acceleration

	PlayerState state; // state
	int is_jump, on_surface;
} Player;

// Prototypes
extern void player_init(Player *player);
extern void player_events(Player *player);
extern void player_update(Player *player);
extern void player_draw(Player *player, int scroll_x);

#endif