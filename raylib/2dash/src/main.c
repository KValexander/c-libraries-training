#include "game.h"

int main(void) {
    Game game;

    /* Initialization */ 
    game_init(&game);
    
    /* Game loop */ 
    game_loop(&game);

    /* Deinitialization */ 
    game_deinit(&game);

    return 0;
}