/* Include libraries */
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

/* Include libraries */
#include <raylib.h>

/* Include files */
#include "helpers.h"
#include "level.h"

/* Level initialization */
void level_init(Level *level) {

	level->frame = 0; // time
	level->count_levels = 0; // count levels
	level->current_level = -1; // current level

	/* Textures initialization */
	load_texture(&level->textures.player, "assets/player.png", 46, 84);
	load_texture(&level->textures.enemy, "assets/enemy.png", 46, 84);
	load_texture(&level->textures.victory, "assets/victory.png", 64, 84);
	load_texture(&level->textures.surface, "assets/surface.png", 384, 64);
	load_texture(&level->textures.platform, "assets/platform.png", 300, 64);

	/* Background initialization */ 
	load_texture(&level->background[0].image, "assets/background.png", 960, 540);
	load_texture(&level->background[1].image, "assets/cloud.png", 1920, 1018);
	level->background[0].scroll = 0.0f;
	level->background[1].scroll = 0.0f;

}

/* OneLevel initialization */ 
void onelevel_init(OneLevel *level) {

	/* Level initialization */
	level->name = "Level"; // level name
	level->count_enemies = 0; // count enemies
	level->count_surfaces = 0; // count surfaces
	level->count_platforms = 0; // count platforms

	/* Camera initialization */
	level->camera.x = 0;
	level->camera.y = 0;

	/* Player initialization */
	level->player.x = 0;
	level->player.y = 0;
	level->player.w = 46;
	level->player.h = 84;

}

/* Loading levels */
void loading_level(Level *level) {

} 

/* Level deinitialization */
void level_deinit(Level *level) {

	/* Textures deinitialization */ 
	UnloadTexture(level->textures.player);
	UnloadTexture(level->textures.enemy);
	UnloadTexture(level->textures.victory);
	UnloadTexture(level->textures.surface);
	UnloadTexture(level->textures.platform);
	UnloadTexture(level->background[0].image);
	UnloadTexture(level->background[1].image);
}

/* Level update */ 
void level_update(Level *level) {

	/* Background update */
	level->background[0].scroll -= 0.1f;
	level->background[1].scroll -= 0.5f;

	/* Background check */
	if(level->background[0].scroll <= -level->background[0].image.width*2) level->background[0].scroll = 0;
	if(level->background[1].scroll <= -level->background[1].image.width*2) level->background[0].scroll = 0;

	printf("%f - %d\n", level->background[0].scroll, -level->background[0].image.width);
	printf("%f - %d\n", level->background[1].scroll, -level->background[1].image.width);

}

/* Level render */ 
void level_render(Level *level) {

	/* Background draw */
	for(int i = 0; i < NUM_BACKGROUNDS; i++) {
		DrawTextureEx(
			level->background[i].image,
			(Vector2){ level->background[i].scroll, 0},
			0.0f,
			1.0f,
			WHITE
		);
		DrawTextureEx(
			level->background[i].image,
			(Vector2){ level->background[i].image.width*2 + level->background[i].scroll, 0},
			0.0f,
			1.0f,
			WHITE
		);
	}

}
