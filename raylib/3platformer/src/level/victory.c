/* Include libraries */
#include <stdio.h>

/* Include libraries */
#include <raylib.h>

/* Include files */
#include "level/victory.h"

/* Victory initialization */ 
void victory_init(Victory *victory) {

	victory->x = 0;
	victory->y = 0;
	victory->w = 64;
	victory->h = 84;

}

/* Victory render */ 
void victory_draw(Victory *victory, Texture2D *texture, Vector2 camera) {
	DrawTexture(
		*texture,
		camera.x + victory->x,
		camera.y + victory->y,
		WHITE
	);
}