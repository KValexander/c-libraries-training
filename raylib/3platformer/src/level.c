/* Include libraries */
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

/* Include libraries */
#include <raylib.h>

/* Include files */
#include "helpers.h"
#include "config.h"
#include "level.h"

/* Level initialization */
void level_init(Level *level) {

	/* Level initialization */ 
	level->frame = 0; // time
	level->count_levels = 0; // count levels
	level->current_level = -1; // current level
	level->is_loading = 0; // check loading level

	/* Entities initialization */
	strcpy(level->entities[0], "player");
	strcpy(level->entities[1], "enemy");
	strcpy(level->entities[2], "victory");
	strcpy(level->entities[3], "surface");
	strcpy(level->entities[4], "platform");
	level->count_entities = sizeof(level->entities) / sizeof(level->entities[0]); // count entities

	/* Textures initialization */
	load_texture(&level->textures.player, "assets/player.png", 46, 84);
	load_texture(&level->textures.enemy, "assets/enemy.png", 46, 84);
	load_texture(&level->textures.victory, "assets/victory.png", 64, 84);
	load_texture(&level->textures.surface, "assets/surface.png", 384, 64);
	load_texture(&level->textures.platform, "assets/platform.png", 300, 64);

	/* Background initialization */
	background_init(level->background);

	/* Loading levels */
	loading_levels(level);

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
	level->player.w = 46;
	level->player.h = 84;

	/* Victory initialization */
	level->victory.w = 64;
	level->victory.h = 86;

}


/* Get filenames from directory */ 
int get_filenames_from_dir(char filenames[MAX_LEVELS][30], int n, char *path) {

	/* Open directory */ 
    struct dirent *dp; // struct dirent
	DIR *dir = opendir("levels");
	if(!dir) return 0; // check dir

	/* Read directory */
	while((dp = readdir(dir)) != NULL) {
        if(strcmp(dp->d_name, ".") && strcmp(dp->d_name, "..")) {
			if(n >= MAX_LEVELS) break;
        	strcpy(filenames[n++], dp->d_name);
        }
	}

	/* Close directory */
	closedir(dir);

	return n;
}

/* Get entity index */
int get_entity_index(Level *level, char *entity) {
	for(int i = 0; i < level->count_entities; i++)
		if(!strcmp(level->entities[i], entity))
			return i;
	return 0;
}

/* Writing OneLevel entity data */
void writing_onelevel_entity_data(OneLevel *level, int index, char values[4][30]) {

	/* FIX */ 
	if(!strcmp(values[0], "0"))
		strcpy(values[0], "1");
	
	/* Writing data */
	switch(index) {

		/* The number corresponds to the number of the entity */
		case 0: // player
			if(!atoi(values[0]) || !atoi(values[1])) break;
			level->player.x = atoi(values[0]);
			level->player.y = atoi(values[1]);
		break;
		case 1: // enemy
			if(!atoi(values[0]) || !atoi(values[1])) break;
			level->enemies[level->count_enemies].x = atoi(values[0]);
			level->enemies[level->count_enemies].y = atoi(values[1]);
			level->enemies[level->count_enemies].w = 46;
			level->enemies[level->count_enemies].h = 84;
			level->count_enemies++;
		break;
		case 2: // victory
			if(!atoi(values[0]) || !atoi(values[1])) break;
			level->player.x = atoi(values[0]);
			level->player.y = atoi(values[1]);
		break;
		case 3: // surface
			if(!atoi(values[0]) || !atoi(values[1])|| !atoi(values[2]) || !atoi(values[3])) break;
			level->surfaces[level->count_surfaces].x = atoi(values[0]);
			level->surfaces[level->count_surfaces].y = atoi(values[1]);
			level->surfaces[level->count_surfaces].w = atoi(values[2]);
			level->surfaces[level->count_surfaces].h = atoi(values[3]);
			level->count_surfaces++;
		break;
		case 4: // platform
			if(!atoi(values[0]) || !atoi(values[1])|| !atoi(values[2]) || !atoi(values[3])) break;
			level->platforms[level->count_platforms].x = atoi(values[0]);
			level->platforms[level->count_platforms].y = atoi(values[1]);
			level->platforms[level->count_platforms].w = atoi(values[2]);
			level->platforms[level->count_platforms].h = atoi(values[3]);
			level->count_platforms++;
		break;

		default: break;

	} 

}

/* Loading levels */
void loading_levels(Level *level) {

	/* Helpers */
	int index; // entity index
	int counter; // counter
	char values[4][30]; // entity values
	char buffer[255]; // buffer
	char *istr; // separator

	/* Get filenames from directory */
	char filenames[MAX_LEVELS][30];
	level->count_levels = get_filenames_from_dir(filenames, level->count_levels, "levels");
	if(!level->count_levels) return; // check for the existence of files

	/* Getting level data from files */
	for(int i = 0; i < level->count_levels; i++) {

		/* OneLevel initialization */
		OneLevel *lv = &level->levels[i];
		onelevel_init(lv);

		/* Concatination */
		strcpy(buffer, filenames[i]);
		sprintf(filenames[i], "levels/%s", buffer);

		/* Open file */ 
		FILE *file = fopen(filenames[i], "r");

		/* Reading file */
		while(fgets(buffer, 255, file) != NULL) {

			/* Clear helpers */
			int index = -1;
			int counter = 0;
			for(int i = 0; i < 4; i++)
				strcpy(values[i], "");

			/* Line splitting */
			istr = strtok(buffer, " ");

			/* Processing parts of a string */
			while(istr != NULL) {
				// printf("%s", istr);

				/* Writing a entity value */
				if(index != -1)
					strcpy(values[counter++], istr);

				/* Get entity index */ 
				else index = get_entity_index(level, istr);

				/* Get the next part of the string */
				istr = strtok(NULL, " ");
			}

			/* Writing OneLevel entity data */
			if(index != -1 && strcmp(values[0], ""))
				writing_onelevel_entity_data(lv, index, values);

		}

		/* Close file */
		fclose(file);

	}

	/* Loading levels success */ 
	level->is_loading = 1;

} 

/* Level deinitialization */
void level_deinit(Level *level) {

	/* Textures deinitialization */ 
	UnloadTexture(level->textures.player);
	UnloadTexture(level->textures.enemy);
	UnloadTexture(level->textures.victory);
	UnloadTexture(level->textures.surface);
	UnloadTexture(level->textures.platform);

	/* Background deinitialization */
	background_deinit(level->background);
}

/* Level update */ 
void level_update(Level *level) {

	/* Background update */
	background_update(level->background);

}

/* Level render */ 
void level_render(Level *level) {

	/* Background draw */
	background_draw(level->background);

}



/* BACKGROUND */
/* ================================ */

/* Background initialization */ 
void background_init(Background *background) {

	/* Main background */ 
	background[0].w = get_screen_width(); // width
	background[0].h = get_screen_height(); // height
	background[0].scroll = 0.0f; // scroll
	background[0].scroll_speed = 0.1f; // scroll speed
	load_texture(
		&background[0].image,
		"assets/background.png",
		background[0].w,
		background[0].h
	); // load texture

	// Cloud background
	background[1].w = 1920; // width
	background[1].h = 1018; // height
	background[1].scroll = 0.0f; // scroll
	background[1].scroll_speed = 0.5f; // scroll speed
	load_texture(
		&background[1].image,
		"assets/cloud.png",
		background[1].w,
		background[1].h
	); // load texture

}

/* Background deinitialization */
void background_deinit(Background *background) {
	for(int i = 0; i < NUM_BACKGROUNDS; i++)
		UnloadTexture(background[i].image);
}

/* Background update */
void background_update(Background *background) {

	/* Scroll update */
	background[0].scroll -= background[0].scroll_speed;
	background[1].scroll -= background[1].scroll_speed;

	/* Check scroll */
	if(background[0].scroll <= -background[0].w) background[0].scroll = 0;
	if(background[1].scroll <= -background[1].w) background[1].scroll = 0;

}

/* Background draw */
void background_draw(Background *background) {

	/* Background draw */
	for(int i = 0; i < NUM_BACKGROUNDS; i++) {
		DrawTextureEx(
			background[i].image, // texture
			(Vector2){ background[i].scroll, 0}, // pos
			0.0f, // rotate
			1.0f, // scale
			WHITE // color
		);
		DrawTextureEx(
			background[i].image, // texture
			(Vector2){ background[i].w + background[i].scroll, 0}, // pos
			0.0f, // rotate
			1.0f, // scale
			WHITE // color
		);
	}

} 

/* ================================ */ 