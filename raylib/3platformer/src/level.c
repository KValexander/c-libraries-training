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
	load_texture(&level->textures.player, "assets/player.png", 256, 348);
	load_texture(&level->textures.enemy, "assets/enemy.png", 264, 360);
	load_texture(&level->textures.victory, "assets/victory.png", 64, 84);
	load_texture(&level->textures.surface, "assets/surface.png", 400, 48);
	load_texture(&level->textures.platform, "assets/platform.png", 300, 48);

	/* Background initialization */
	background_init(level->background);

	/* Loading levels */
	loading_levels(level);

	/* Change levels */
	level_change(level, 0);

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

/* Check level existence */
int level_check(Level *level, int n) {
	return (n >= 0 && n < level->count_levels);
}

/* Change current level */ 
void level_change(Level *level, int n) {

	/* Check level existence */
	if(!level_check(level, n)) return;
	
	/* Change current level */ 
	level->current_level = n;

	/* Level initialization */
	onelevel_init(&level->levels[level->current_level]);

}

/* OneLevel preinitialization */
void onelevel_preinit(OneLevel *level) {
	level->access = 0; // passed
	level->name = "Level"; // level name
	level->count_enemies = 0; // count enemies
	level->count_surfaces = 0; // count surfaces
	level->count_platforms = 0; // count platforms
} 

/* OneLevel initialization */ 
void onelevel_init(OneLevel *level) {
	/* Level frame */
	level->frame = 0;

	/* Level access */ 
	level->access = 1;

	/* Level state */
	level->state = LEVEL_STOP;

	/* Camera initialization */
	level->camera.x = 0;
	level->camera.y = 0;

	/* Player initialization */
	player_init(&level->player);

	/* Player start position */ 
	level->player.x = level->start_player.x;
	level->player.y = level->start_player.y;

	/* Victory initialization */
	victory_init(&level->victory);

	/* Victory start position */ 
	level->victory.x = level->start_victory.x;
	level->victory.y = level->start_victory.y;

	/* Enemies initialization */
	for(int i = 0; i < level->count_enemies; i++) {
		enemy_init(&level->enemies[i]);
		
		/* Enemy start position */ 
		level->enemies[i].x = level->start_enemies[i].x;
		level->enemies[i].y = level->start_enemies[i].y;
	} 


	/* Surfaces initialization */
	for(int i = 0; i < level->count_surfaces; i++) {
		surface_init(&level->surfaces[i]);
	
		/* Surface start position */ 
		level->surfaces[i].x = level->start_surfaces[i].x;
		level->surfaces[i].y = level->start_surfaces[i].y;
	}

	/* Platforms initialization */
	for(int i = 0; i < level->count_platforms; i++) {
		platform_init(&level->platforms[i]);
		
		/* Platforms start position */ 
		level->platforms[i].x = level->start_platforms[i].x;
		level->platforms[i].y = level->start_platforms[i].y;
	}

	/* Level state */
	level->state = LEVEL_PLAY;

}

/* Level update */ 
void level_update(Level *level) {
	if(!level->is_loading || level->current_level == -1) return;
	
	/* Current level */
	OneLevel *lv = &level->levels[level->current_level];
	lv->frame++; // time

	/* Restart */
	if(IsKeyPressed(KEY_R))
		level_change(level, level->current_level);

	/* Next level */
	if(lv->state == LEVEL_VICTORY)
		if(IsKeyPressed(KEY_N))
			level_change(level, level->current_level + 1);

	/* Level state LEVEL PLAY */
	if(lv->state == LEVEL_PLAY) {

		/* Background update */
		background_update(level->background);

		/* Player update */
		player_update(&lv->player, lv->frame);
		lv->player.dy += GRAVITY; // gravity
		if(lv->player.y > get_screen_height() + 300)
			lv->state = LEVEL_GAMEOVER;

		/* Enemies update */
		for(int i = 0; i < lv->count_enemies; i++) {
			enemy_update(&lv->enemies[i], lv->frame);
			if(!lv->enemies[i].is_dead) {
				lv->enemies[i].dy += GRAVITY; // gravity
				if(lv->enemies[i].y > get_screen_height() + 300)
					lv->enemies[i].is_dead = 1;
			}
		}

		/* Camera update */
	    lv->camera.x = -lv->player.x + (get_screen_width() / 2 - lv->player.w / 2);
	    lv->camera.y = -lv->player.y + (get_screen_height() / 2 - lv->player.h / 2);
	    if(lv->camera.x > 0) lv->camera.x = 0;
		if(lv->camera.y < 0) lv->camera.y = 0;

		/* Collisions */
		onelevel_collisions(lv);

	} 

}

/* OneLevel collision */
void onelevel_collisions(OneLevel *level) {
	int side;

	float px = level->player.x, py = level->player.y;
	float pw = level->player.w, ph = level->player.h;

	/* Check victory */
	if(collide_2d( px, py, level->victory.x, level->victory.y, pw, ph, level->victory.w, level->victory.h )) level->state = LEVEL_VICTORY;

	/* Enemies collision */
	for(int i = 0; i < level->count_enemies; i++)
		if(collide_2d(
			level->enemies[i].x + level->enemies[i].w / 4,
			level->enemies[i].y + level->enemies[i].h / 4,
			px + pw / 4, py + ph / 4,
			level->enemies[i].w / 2,
			level->enemies[i].h / 2,
			pw / 2, ph / 2
		)) level->state = LEVEL_GAMEOVER;

	/* Surfaces collision */
	for(int i = 0; i < level->count_surfaces; i++) {
		float sx = level->surfaces[i].x, sy = level->surfaces[i].y;
		float sw = level->surfaces[i].w, sh = level->surfaces[i].h;

		/* With player */
		player_on_surface(&level->player, surface_collision(&level->surfaces[i], px, py, pw, ph), sx, sy, sw, sh);

		/* With enemies */
		for(int i = 0; i < level->count_enemies; i++)
			if(collide_2d(
				level->enemies[i].x,
				level->enemies[i].y,
				sx, sy,
				level->enemies[i].w,
				level->enemies[i].h,
				sw, sh
			)) {
				level->enemies[i].dy = 0;
				level->enemies[i].is_jump = 1;
			}
	}

	/* Platforms collision */
	for(int i = 0; i < level->count_platforms; i++) {
		float fx = level->platforms[i].x, fy = level->platforms[i].y;
		float fw = level->platforms[i].w, fh = level->platforms[i].h;

		/* With player */
		player_on_surface(&level->player, platform_collision(&level->platforms[i], px, py, pw, ph), fx, fy, fw, fh);

		/* With enemies */
		for(int i = 0; i < level->count_enemies; i++)
			if(collide_2d(
				level->enemies[i].x,
				level->enemies[i].y,
				fx, fy,
				level->enemies[i].w,
				level->enemies[i].h,
				fw, fh
			)) {
				level->enemies[i].dy = 0;
				level->enemies[i].is_jump = 1;
			}
			
	}

}

/* Level render */ 
void level_render(Level *level) {
	if(!level->is_loading || level->current_level == -1) return;
	
	/* Current level */
	OneLevel *lv = &level->levels[level->current_level];

	/* Background draw */
	background_draw(level->background);

	/* Player render */
	player_draw(&lv->player, &level->textures.player, lv->camera);

	/* Victory render */ 
	victory_draw(&lv->victory, &level->textures.victory, lv->camera);

	/* Enemies render */
	for(int i = 0; i < lv->count_enemies; i++)
		enemy_draw(&lv->enemies[i], &level->textures.enemy, lv->camera);

	/* Surfaces render */
	for(int i = 0; i < lv->count_surfaces; i++)
		surface_draw(&lv->surfaces[i], &level->textures.surface, lv->camera);

	/* Platforms render */
	for(int i = 0; i < lv->count_platforms; i++)
		platform_draw(&lv->platforms[i], &level->textures.platform, lv->camera);

	/* VICTORY */ 
	if(lv->state == LEVEL_VICTORY) {
		level->levels[level->current_level + 1].access = 1;
		DrawText("VICTORY", 20, 30, 36, DARKGREEN); 
		DrawText("R for restart", 20, 80, 24, DARKGREEN);
		DrawText("M to select level", 20, 110, 24, DARKGREEN); 
		if(level_check(level, level->current_level+1))
			DrawText("N for next level", 20, 140, 24, DARKGREEN); 
	}

	/* GAMEOVER*/
	else if(lv->state == LEVEL_GAMEOVER) {
		DrawText("GAMEOVER", 20, 30, 36, MAROON); 
		DrawText("R for restart", 20, 80, 24, MAROON); 
		DrawText("M to select level", 20, 110, 24, MAROON); 
	}

}


/* LOADING LEVELS */ 
/* ================================ */

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
	
	/* Writing data */
	switch(index) {

		/* The number corresponds to the number of the entity */
		case 0: // player
			// if(!atoi(values[0]) || !atoi(values[1])) break;
			level->start_player.x = atoi(values[0]);
			level->start_player.y = atoi(values[1]);
		break;
		case 1: // enemy
			// if(!atoi(values[0]) || !atoi(values[1])) break;
			level->start_enemies[level->count_enemies].x = atoi(values[0]);
			level->start_enemies[level->count_enemies].y = atoi(values[1]);
			level->count_enemies++;
		break;
		case 2: // victory
			// if(!atoi(values[0]) || !atoi(values[1])) break;
			level->start_victory.x = atoi(values[0]);
			level->start_victory.y = atoi(values[1]);
		break;
		case 3: // surface
			// if(!atoi(values[0]) || !atoi(values[1])) break;
			level->start_surfaces[level->count_surfaces].x = atoi(values[0]);
			level->start_surfaces[level->count_surfaces].y = atoi(values[1]);
			level->count_surfaces++;
		break;
		case 4: // platform
			// if(!atoi(values[0]) || !atoi(values[1])) break;
			level->start_platforms[level->count_platforms].x = atoi(values[0]);
			level->start_platforms[level->count_platforms].y = atoi(values[1]);
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

		/* OneLevel preinitialization */
		OneLevel *lv = &level->levels[i];
		onelevel_preinit(lv);

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