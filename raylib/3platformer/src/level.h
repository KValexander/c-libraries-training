#ifndef LEVEL_H_
#define LEVEL_H_

/* Constants */
#define GRAVITY 0.4f
#define NUM_BACKGROUNDS 2
#define MAX_LEVELS 10
#define MAX_ENEMIES 100
#define MAX_SURFACES 100
#define MAX_PLATFORMS 1000

/* Include libraries */
#include <raylib.h> 

/* Enum State*/
typedef enum {
	LEVEL_STOP = 0,
	LEVEL_PLAY,
	LEVEL_GAMEOVER,
	LEVEL_WIN
} State;

/* Struct Textures */
typedef struct {
	Texture2D player;
	Texture2D enemy;
	Texture2D victory;
	Texture2D surface;
	Texture2D platform;
} Textures; 

/* Struct Background */
typedef struct {
	Texture2D image;
	float scroll;
} Background;

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
	Object camera; // struct Object, camera
	Object player; // struct Object, player
	Object victory; // struct Object, victory zone
	Object enemies[MAX_ENEMIES]; // struct Object, array of enemies
	Object surfaces[MAX_SURFACES]; // struct Object, array of surfaces
	Object platforms[MAX_PLATFORMS]; // struct Object, array of platforms
} OneLevel;

/* Struct Level */
typedef struct {
	int frame; // time
	int count_levels; // count levels
	int current_level; // current level
	
	Textures textures; // struct Textures
	Background background[NUM_BACKGROUNDS]; // struct Background, array
	OneLevel levels[MAX_LEVELS]; // struct Object, array of levels
} Level;

/* Prototypes */
extern void level_init(Level *level); // level initialization
extern void onelevel_init(OneLevel *level); // one level initialization
extern void level_deinit(); // level deinitialization

extern void loading_levels(Level *level); // loading levels

extern int level_check(Level *level, int n); // check level existence
extern void level_change(Level *level, int n); // change current level

extern void level_update(Level *level); // level update
extern void level_render(Level *level); // level render

#endif