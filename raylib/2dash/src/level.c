/* Include libraries */
#include <stdio.h>
#include <dirent.h>
#include <string.h>

/* Include libraries */ 
#include <raylib.h>

/* Include files */
#include "level.h"

/* Level initialization */
void level_init(Levels *levels) {

	/* Loading levels */ 
	level_loading(levels);
	levels->current = -1; // current level

}

/* Loading levels */
void level_loading(Levels *levels) {
	struct dirent *dr;
	char contents[100]; // folder contents

	/* Open folder */ 
	DIR *dir = opendir("levels");
	if(!dir) return;

	/* Get the contents of a folder */ 
	while((dr = readdir(dir)) != NULL) {
		strcat(contents, "\n");
		strcat(contents, dr->d_name);
	}

	printf("%d\n", strlen(contents));

	/* Close folder */ 
	closedir(dir);
}