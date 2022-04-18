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

	/* Change level */ 
	if(n >= 0 || n <= levels->count_levels)
		levels->current_level = n;

	/* Level */ 
	Level *level = &levels->levels[levels->current_level];
	level->frame = 0; // time
	level->is_victory = 0; // state

	/* Player initialization */
	player_init(&level->player);
	level->player.x = level->start_player.x;
	level->player.y = level->start_player.y;

}

/* Update level */
void level_update(Levels *levels) {
	if(levels->current_level < 0) return; // check

	/* Restart */
	if(IsKeyDown(KEY_R))
		level_change(levels, levels->current_level);

	/* Level */ 
	Level *level = &levels->levels[levels->current_level];
	level->frame++; // time

	/* Level processing */ 
	if(!level->is_victory) {

		/* Update player */
		player_update(&level->player, LEVEL_GRAVITY, LEVEL_ACCELERATION);

	    /* Camera update */
	    level->camera.x = -level->player.x + (960 / 2 - level->player.w / 2);
	    level->camera.y = -level->player.y + (540 / 2 - level->player.h / 2);
	    if(level->camera.x > 0) level->camera.x = 0;
	    if(level->camera.y < 0) level->camera.y = 0;

	    /* Level collisions */
	    level_collisions(levels);

	}

}

/* Check collision */
int collide_2d(float x1, float y1, float x2, float y2, float wt1, float ht1, float wt2, float ht2) {
    return (!((x1 > (x2+wt2)) || (x2 > (x1+wt1)) || (y1 > (y2+ht2)) || (y2 > (y1+ht1))));
}

/* Level collisions */
void level_collisions(Levels *levels) {
	Level *level = &levels->levels[levels->current_level];

	/* Check victory */
	if(collide_2d(
		level->player.x,
		level->player.y,
		level->victory_condition.x,
		level->victory_condition.y,
		level->player.w,
		level->player.h,
		level->victory_condition.w,
		level->victory_condition.h
	)) level->is_victory = 1;

	/* Check rect collision */
	for(int i = 0; i <= level->count_rects; i++) {

		/* Player data */
		float px = level->player.x, py = level->player.y;
		float pw = level->player.w, ph = level->player.h;
		
		/* Rect data */
		float rx = level->rects[i].x, ry = level->rects[i].y;
		float rw = level->rects[i].w, rh = level->rects[i].h;

		/* Up */
		if(px + pw > rx && px < rx + rw) {
			if(py + ph > ry && py < ry) {
				level->player.y = ry - ph;
				py = level->player.y;

				level->player.dy = 0;
				level->player.is_jump = 1;
				level->player.on_surface = 1;
			}
		}

		/* Sides */
		if(py + ph > ry && py < ry + rh) {
			
			/* Left */
			if(px + pw > rx && px < rx) {
				level->player.x = rx - pw;
				px = level->player.x;

				level->player.dx = 0;
			}
			
			/* Right */
			else if(px < rx + rw && px > rx + rw) {
				level->player.x = rx + rw;
				px = level->player.x;

				level->player.dx = 0;
			}

		}

	}

}

/* Render level */
void level_render(Levels *levels) {
	if(levels->current_level < 0) return; // check
	ClearBackground(LIGHTGRAY); // background
	
	/* Level */
	Level *level = &levels->levels[levels->current_level]; // level

	/* Draw player */
	player_draw(&level->player, level->camera.x, level->camera.y);

	/* Draw victory zone */
	DrawRectangle(
		level->camera.x + level->victory_condition.x,
		level->camera.y + level->victory_condition.y,
		level->victory_condition.w,
		level->victory_condition.h,
		DARKGREEN
	);

	/* Draw rects */
	for(int i = 0; i <= level->count_rects; i++)
		DrawRectangle(
			level->camera.x + level->rects[i].x,
			level->camera.y + level->rects[i].y,
			level->rects[i].w,
			level->rects[i].h,
			DARKGRAY
		);

	/* Level victory */
	if(level->is_victory) {
		/* Draw text */
		DrawText("You victory!", 30, 20, 48, DARKGREEN);
		DrawText("R for restart!", 30, 80, 36, DARKGREEN);
	}

	/* Player is dead */
	else if(level->player.state == PLAYER_STATE_DYING) {
		/* Draw text */
		DrawText("You lose!", 30, 20, 48, MAROON);
		DrawText("R for restart!", 30, 80, 36, MAROON);
	}

}





/* One level initialization */
void level_one_init(Level *level) {
	level->difficulty = -1; // difficulty
	level->count_rects = -1; // count rects
	level->is_victory = 0; // state

	/* Player start position */ 
	level->start_player.x = 0;
	level->start_player.y = 0;

	/* Camera */
	level->camera.x = 0;
	level->camera.y = 0;

	/* Victory condition */
	level->victory_condition.x = 0;
	level->victory_condition.y = 0;
	level->victory_condition.w = 0;
	level->victory_condition.h = 0;
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
		Level *level = &levels->levels[i]; // level
		strcpy(level->name, filenames[i]); // level name
		level_one_init(level);

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

				/* Writing properties */ 
				if(strcmp(current, "")) {
					properties[n] = atoi(istr); n++;
				}

				/* Player */ 
				if(!strcmp(istr, "player"))
					strcpy(current, "player");

				/* Difficulty */
				else if(!strcmp(istr, "difficulty"))
					strcpy(current, "difficulty");

				/* Victory */
				else if(!strcmp(istr, "victory"))
					strcpy(current, "victory");

				/* Rect */ 
				else if(!strcmp(istr, "rect")) {
					strcpy(current, "rect");
					level->count_rects++;
				}

				/* Get a new part of the line */ 
				istr = strtok(NULL, " ");
			}

			/* Writing data */
			/* Player start position */
			if(!strcmp(current, "player")) {
				level->start_player.x = properties[0];
				level->start_player.y = properties[1];
			}

			/* Victory */
			else if(!strcmp(current, "victory")) {
				level->victory_condition.x = properties[0];
				level->victory_condition.y = properties[1];
				level->victory_condition.w = properties[2];
				level->victory_condition.h = properties[3];
			}

			/* Difficulty */
			else if(!strcmp(current, "difficulty"))
				level->difficulty = properties[0];

			/* Rects */
			else if(!strcmp(current, "rect")) {
				if(level->count_rects < MAX_RECTS) {
					level->rects[level->count_rects].x = properties[0];
					level->rects[level->count_rects].y = properties[1];
					level->rects[level->count_rects].w = properties[2];
					level->rects[level->count_rects].h = properties[3];
				}
			}

		}

		fclose(file); // close file

		/* Restrictions */
		if(level->count_rects >= MAX_RECTS)
			level->count_rects = MAX_RECTS - 1;
	}

	/* Close folder */ 
	closedir(dir);
}