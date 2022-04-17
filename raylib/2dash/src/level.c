/* Include libraries */
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

/* Include libraries */ 
#include <raylib.h>

/* Include files */
#include "level.h"

/* Level initialization */
void level_init(Levels *levels) {
	levels->current_level = -1; // current level
	levels->count_levels = -1; // count levels

	/* Loading levels */ 
	level_loading(levels);

	for(int i = 0; i <= levels->count_levels; i++) {
		printf("%s:\n", levels->levels[i].name);
		for(int j = 0; j <= levels->levels[i].count_rects; j++) {
			printf("%d - %d - %d - %d\n",
				levels->levels[i].rects[j].x,
				levels->levels[i].rects[j].y,
				levels->levels[i].rects[j].w,
				levels->levels[i].rects[j].h
			);
		}
	}

}

/* Change level */
void level_change(Levels *levels, int n) {
	if(n >= 0 || n <= levels->count_levels)
		levels->current_level = n;

	/* Level */ 
	Level *level = &levels->levels[levels->current_level];

	/* Player initialization */
	player_init(&level->player);

	/* Camera initialization */
	level->camera.x = 0;
	level->camera.y = 0;
}

/* Update level */
void level_update(Levels *levels) {
	if(levels->current_level < 0) return; // check

	/* Level */ 
	Level *level = &levels->levels[levels->current_level];

	/* Player events */
	player_events(&level->player);

    /* Camera update */
    level->camera.x = -level->player.x + (960 / 2 - level->player.w / 2);
    if(level->camera.x > 0) level->camera.x = 0;
}

/* Render level */
void level_render(Levels *levels) {
	if(levels->current_level < 0) return; // check
	ClearBackground(LIGHTGRAY); // background
	
	/* Level */
	Level *level = &levels->levels[levels->current_level]; // level

	/* Draw player */
	player_draw(&level->player, level->camera.x);

	/* Draw rects */
	for(int i = 0; i <= level->count_rects; i++)
		DrawRectangle(
			level->camera.x + level->rects[i].x,
			level->rects[i].y,
			level->rects[i].w,
			level->rects[i].h,
			DARKGRAY
		);

}








/* Loading levels */
void level_loading(Levels *levels) {
	struct dirent *dr; // struct dirent
	/* Helpers */
	int n = 0; // counter
	char line[255]; // file line
	/* Helpers for line */ 
	char *istr;
	int properties[4]; // properties shapes
	char current[20]; // current type

	/* Array of filenames*/ 
	char filenames[MAX_LEVELS][30];

	/* Buffer */
	int buffer_length = MAX_LEVELS + 2;
	char buffer[buffer_length][30];
	for(int i = 0; i < buffer_length; i++)
		strcpy(buffer[i], "");

	/* Open folder */ 
	DIR *dir = opendir("levels");
	if(!dir) return;

	/* Get the contents of a folder */ 
	while((dr = readdir(dir)) != NULL) {
		if(n > buffer_length) break;
		strcpy(buffer[n], dr->d_name);
		n++;
	}

	/* Get the names of existing levels */
	for(int i = 2; i < buffer_length; i++) {
		if(strcmp(buffer[i], "")) {
			levels->count_levels++;
			strcpy(filenames[levels->count_levels], buffer[i]);
		}
	}

	/* Get level data */
	for(int i = 0; i <= levels->count_levels; i++) {
		/* Level initialization */
		Level *level = &levels->levels[i];
		strcpy(level->name, filenames[i]);
		level->difficulty = -1;
		level->count_rects = -1;
		level->state = 0;

		/* Concatenation */ 
		strcpy(line, filenames[i]);
		sprintf(filenames[i], "levels/%s", line);

		/* Get data from a file */
		FILE *file = fopen(filenames[i], "r"); // open file

		/* Reading lines */ 
		while(fgets(line, 255, file) != NULL) {
			strcpy(current, ""); n = 0;
			
			/* Split line by space */ 
			istr = strtok(line, " ");
			while(istr != NULL) {

				/* Rect properties */ 
				if(!strcmp(current, "rect")) {
					properties[n] = atoi(istr);
					n++;
				}

				/* Difficulty properties */ 
				else if(!strcmp(current, "difficulty")) {
					properties[n] = atoi(istr);
					n++;
				}

				/* Difficulty */
				if(!strcmp(istr, "difficulty"))
					strcpy(current, "difficulty");

				/* Rect */ 
				else if(!strcmp(istr, "rect")) {
					strcpy(current, "rect");
					level->count_rects++;
				}

				/* Get a new part of the line */ 
				istr = strtok(NULL, " ");
			}

			/* Writing data */
			/* Difficulty */
			if(!strcmp(current, "difficulty"))
				level->difficulty = properties[0];

			/* Rects */
			else if(!strcmp(current, "rect")) {
				if(level->count_rects < MAX_LEVELS) {
					level->rects[level->count_rects].x = properties[0];
					level->rects[level->count_rects].y = properties[1];
					level->rects[level->count_rects].w = properties[2];
					level->rects[level->count_rects].h = properties[3];
				}
			}

		}

		fclose(file); // close file

		/* Restrictions */
		if(level->count_rects >= MAX_LEVELS)
			level->count_rects = MAX_LEVELS - 1;
	}

	/* Close folder */ 
	closedir(dir);
}