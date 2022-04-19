/* Include files */
#include "config.h"
#include "screen.h"

int main(void) {
    Screen screen;

    /* Load configuration */
    load_config();

    /* Initialization */ 
    screen_init(&screen);
    
    /* Game loop */
    screen_loop(&screen);

    /* Deinitialization */ 
    screen_deinit(&screen);

    return 0;
}