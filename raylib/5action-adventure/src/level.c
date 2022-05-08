/* Include libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Include files */
#include "level.h"

/* Initialization */ 
void level_init(Level *level, Textures *textures) {
	level->frame = 0; // time

	/* Camera */
	level->camera.x = 0;
	level->camera.y = 0;

	/* Textures */
	level->textures = textures;

	/* Map */
	level->map = get_texture(level->textures, "map");

	/* Player */
	level->player_onload = 0; // player onload state
	
	/* Tiles */ 
	level->count_tiles = 0; // count tiles

	/* Create map */
	level_create_map(level);

}

/* Create tile */
void level_create_tile(Level *level, Position pos, Color color, int collision) {
	if(level->count_tiles >= MAX_TILES) return;
	level->tiles[level->count_tiles++] = create_tile(
		(Rect) { pos.x, pos.y, TILESIZE, TILESIZE },
		color,
		collision
	);
}

/* Create player */
void level_create_player(Level *level, Position pos, Color color, int speed) {
	level->player = create_player(
		(Rect) { pos.x, pos.y, 64, 64 },
		color,
		speed,
		&level->count_tiles,
		level->tiles // I don't know why the pointer is passed in this way
	); level->player_onload = 1;
} 

/* Create map */
void level_create_map(Level *level) {
	char concat[30]; // string to concatenate
	Position pos; // tile position

	/* Create layouts */
	create_layout(level, "boundary", "assets/map/map_FloorBlocks.csv");
	create_layout(level, "grass", "assets/map/map_Grass.csv");
	create_layout(level, "object", "assets/map/map_Objects.csv");

	/* Create map from layouts */
	for(int l = 0; l < level->count_layouts; l++) {
		Layout *layout = &level->layouts[l];

		/* Create layer */
		for(int i = 0; i < layout->rows; i++) {
			for(int j = 0; j < layout->columns; j++) {
				/* Checking for the absence of a tile */ 
				if(layout->layout[i][j] != -1) {

					/* Tile rect */
					pos.x = j * TILESIZE;
					pos.y = i * TILESIZE;

					/* Boundary */
					if(!strcmp(layout->name, "boundary"))
						level_create_tile(level, pos, BLANK, 1);

					/* Grass and Object */
					else {
						level_create_tile(level, pos, WHITE, 1);
						tile_give_texture(&level->tiles[level->count_tiles - 1], get_texture_by_id(level->textures, layout->layout[i][j]));
					}

				}
			}
		}

	} 

	/* Create player */ 
	level_create_player(level, (Position) { 2000, 1430 }, BLACK, 5);
	player_give_texture(&level->player, get_texture(level->textures, "player"));

}

/* Camera update */
void camera_update(Position *camera, Rect *rect) {

	camera->x = -rect->x + (WIDTH / 2 - rect->w / 2);
	camera->y = -rect->y + (HEIGHT / 2 - rect->h / 2);

}

/* Level update */
void level_update(Level *level) {
	level->frame++; // time

	/* Player update */
	if(level->player_onload)
		player_update(&level->player);

	/* Camera update */
	camera_update(&level->camera, &level->player.rect);

} 

/* Level render */
void level_render(Level *level) {

	/* Draw map */
	DrawTexture(level->map.texture, level->camera.x, level->camera.y, WHITE);

	/* Draw tiles */
	for(int i = 0; i < level->count_tiles; i++)
		tile_draw(&level->tiles[i], level->camera);

	/* Draw player */
	if(level->player_onload)
		player_draw(&level->player, level->camera);

}

/* Create layout */
void create_layout(Level *level, char *name, char *path) {
	if(level->count_layouts >= MAX_LAYOUTS) return;
	level->layouts[level->count_layouts++] = load_layout(name, path);
}

/* Load layout from file */
Layout load_layout(char *name, char *path) {

	/* Create layout */
	Layout layout;

	/* Naming */ 
	strcpy(layout.name, name);

	/* Rows and Columns */ 
	layout.rows = 0;
	layout.columns = 0;

	/* Open file */
	FILE *file = fopen(path, "r");
	char buffer[255]; // buffer
	char *istr; // separator

	/* Read file */
	while(fgets(buffer, 255, file) != NULL) {
		if(layout.rows >= MAX_ROWS) break;

		/* Line splitting */
		istr = strtok(buffer, ",");
		layout.columns = 0;

		/* Processing parts of a string */
		while(istr != NULL) {
			if(layout.columns >= MAX_COLUMNS) break;
			// printf("%d - %s\n", layout.columns, istr);

			/* Adding a number to an array */
			layout.layout[layout.rows][layout.columns++] = atoi(istr);

			/* Get the next part of the string */
			istr = strtok(NULL, ",");
		}

		layout.rows++;
	}

	/* Close file */ 
	fclose(file);

	printf("%s - %d - %d \n", layout.name, layout.rows, layout.columns);

	/* Return layout */
	return layout;

}