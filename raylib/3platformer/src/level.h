#ifndef LEVEL_H_
#define LEVEL_H_

/* Constants */
#define GRAVITY 0.4f
#define MAX_LEVELS 10
#define MAX_ENEMIES 100
#define MAX_SURFACES 100
#define MAX_PLATFORMS 1000

/* Include libraries */
#include <raylib.h> 

/* Include files */
#include "level/background.h"
#include "level/player.h"
#include "level/enemy.h"
#include "level/victory.h"
#include "level/surface.h"
#include "level/platform.h"

/* Enum State*/
typedef enum {
	LEVEL_STOP = 0,
	LEVEL_PLAY,
	LEVEL_GAMEOVER,
	LEVEL_VICTORY
} State;

/* Struct Textures */
typedef struct {
	Texture2D player;
	Texture2D enemy;
	Texture2D victory;
	Texture2D surface;
	Texture2D platform;
} Textures; 

/* Struct Object */
typedef struct {
	int x, y, w, h;
} Object;

/* Struct OneLevel */
typedef struct {
	char *name; // level name
	int count_enemies; // count enemies
	int count_surfaces; // count enemies
	int count_platforms; // count platforms

	State state; // level state

	/* Starting positions of objects */ 
	Object start_camera; // camera
	Object start_player; // player
	Object start_victory; // victory
	Object start_enemies[MAX_ENEMIES]; // enemies
	Object start_surfaces[MAX_ENEMIES]; // surfaces
	Object start_platforms[MAX_ENEMIES]; // platforms

	/* Objects */ 
	Vector2 camera; // struct Vector2, camera
	Player player; // struct Player
	Victory victory; // struct Victory
	Enemy enemies[MAX_ENEMIES]; // struct Enemy, array
	Surface surfaces[MAX_SURFACES]; // struct Surface, array
	Platform platforms[MAX_PLATFORMS]; // struct Platform, array
} OneLevel;

/* Struct Level */
typedef struct {
	int frame; // time
	int count_levels; // count levels
	int current_level; // current level

	int is_loading; // check loading level

	/* List of level entities */ 
	char entities[5][30];
	int count_entities; // count entities
	
	Textures textures; // struct Textures
	Background background[NUM_BACKGROUNDS]; // struct Background, array
	OneLevel levels[MAX_LEVELS]; // struct Object, array of levels
} Level;

/* Prototypes */
extern void level_init(Level *level); // level initialization
extern void level_deinit(); // level deinitialization
extern void onelevel_preinit(OneLevel *level); // one level preinitialization
extern void onelevel_init(OneLevel *level); // one level initialization

extern int level_check(Level *level, int n); // check level existence
extern void level_change(Level *level, int n); // change current level

extern void onelevel_collisions(OneLevel *level); // onelevel collisions
extern void level_update(Level *level); // level update
extern void level_render(Level *level); // level render

/* Loading levels prototypes */ 
extern int get_filenames_from_dir(char filenames[MAX_LEVELS][30],
								  int n, char *path); // get filenames from directory
extern int get_entity_index(Level *level, char *entity); // get entity index
extern void writing_onelevel_entity_data(OneLevel *level,
					int index, char values[4][30]); // writing onelevel entuty data
extern void loading_levels(Level *level); // loading levels

#endif