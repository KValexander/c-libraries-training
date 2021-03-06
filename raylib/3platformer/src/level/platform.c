/* Include libraries */
#include <stdio.h>

/* Include libraries */
#include <raylib.h>

/* Include files */
#include "helpers.h"
#include "level/platform.h"

/* Platform initialization */ 
void platform_init(Platform *platform) {

	platform->x = 0;
	platform->y = 0;
	platform->w = 300;
	platform->h = 48;

}

/* Platform collision */
int platform_collision(Platform *platform, float x, float y, float w, float h){
	
	/* Getting the side of the collision */
	return sides_collision(x, y, platform->x, platform->y, w, h, platform->w, platform->h);
}

/* Platform render */ 
void platform_draw(Platform *platform, Texture2D *texture, Vector2 camera) {
	DrawTexture(
		*texture,
		camera.x + platform->x,
		camera.y + platform->y,
		WHITE
	);
}