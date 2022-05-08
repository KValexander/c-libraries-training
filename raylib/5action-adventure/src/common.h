#ifndef COMMON_H_
#define COMMON_H_

/* Include libraries */
#include <dirent.h>
#include <string.h>

/* Common contsants */
#define WIDTH 	960 // window screen
#define HEIGHT 	540 // window height
#define FPS 	60  // FPS
#define TILESIZE 64 // tile size
 
/* Common structs */ 
/* Struct Position */
typedef struct Position {
	float x, y;
} Position;

/* Struct Rect */
typedef struct Rect {
	float x, y, w, h;
} Rect;

/* Collide */
static int collide(float x1, float y1, float x2, float y2, float w1, float h1, float w2, float h2) {
    return (!((x1 > (x2+w2)) || (x2 > (x1+w1)) || (y1 > (y2+h2)) || (y2 > (y1+h1))));
}

/* Get filenames from directory */ 
static int get_filenames_from_dir(char *filenames[30], int n, char *path) {

	/* Open directory */ 
    struct dirent *dp; // struct dirent
	DIR *dir = opendir("levels");
	if(!dir) return 0; // check dir

	/* Read directory */
	while((dp = readdir(dir)) != NULL) {
        if(strcmp(dp->d_name, ".") && strcmp(dp->d_name, "..")) {
			if(n >= 100) break;
        	strcpy(filenames[n++], dp->d_name);
        }
	}

	/* Close directory */
	closedir(dir);

	return n;
}

#endif