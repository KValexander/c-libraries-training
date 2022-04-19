/* Include libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Include files */
#include "config.h"

/* Get screen width */
int get_screen_width() {
	return config_screen_width;
}

/* Get screen height */ 
int get_screen_height() {
	return config_screen_height;
}

/* Get screen height */ 
int get_screen_fps() {
	return config_screen_fps;
}

/* Get screen height */ 
char *get_screen_title() {
	return config_screen_title;
}

/* Loading configurations from a file */ 
void load_config() {

	/* All properties */ 
	char *properties[] = {
		"WIDTH", "HEIGHT", "FPS", "TITLE"
	}; int count_prop = sizeof(properties) / sizeof(properties[0]);

	/* Helpers */ 
	int prop; // property
	char value[20]; // property values
	char *istr; // separator

	/* Open file */
	FILE *file = fopen("config.txt", "r");
	char buffer[30]; // buffer for line

	/* If the file does not exist */ 
	if(file == NULL) return;

	/* Read file */
	while(fgets(buffer, 30, file) != NULL) {

		/* Clear helpers */
		prop = -1;
		strcpy(value, "");

		/* Line splitting */
		istr = strtok(buffer, "=");

		/* Processing parts of a string */
		while(istr != NULL) {

			/* Writing a property value */
			if(prop != -1)
				strcpy(value, istr);

			/* Check properties */
			for(int i = 0; i < count_prop; i++)
				if(!strcmp(properties[i], istr))
					prop = i;

			/* Get the second part of a string */
			istr = strtok(NULL, "=");
		}

		/* Writing data to variables */
		if(prop != -1 && strcmp(value, "")) {
			switch(prop) {

				/* Numbering according to the properties array */ 
				case 0: // screen width
					if(!atoi(value)) break;
					config_screen_width = atoi(value);
				break;
				case 1: // screen height
					if(!atoi(value)) break;
					config_screen_height = atoi(value);
				break;
				case 2: // screen fps
					if(!atoi(value)) break;
					config_screen_fps = atoi(value);
				break;
				case 3: // screen title
					strcpy(config_screen_title, value);
				break;
				
				default: break;

			}
		}

	}

	/* Close file */
	fclose(file);

}