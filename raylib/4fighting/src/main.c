/* Include files */ 
#include "common.h"
#include "game.h"

/* Game entry point */ 
int main() {

	/* Struct Game */ 
	Game game;

	/* Game initialization */ 
	game_init(&game);

	/* Game loop */ 
	game_loop(&game);
	
	/* Game deinitialization */ 
	game_deinit(&game);

}