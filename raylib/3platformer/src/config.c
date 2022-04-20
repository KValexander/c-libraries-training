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

/* Get property index */
int get_property_index(char *prop) {
	for(int i = 0; i < config_count_prop; i++)
		if(!strcmp(config_properties[i], prop))
			return i;
	return -1;
}

/* Update config property */ 
void update_config_prop(int index, char *value) {

	/* Update property */ 
	switch(index) {

		/* Numbering according to the config properties array */ 
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

/* Change config propery */
void change_config_prop(char *prop, char *value) {

	/* Get property index */ 
	int index = get_property_index(prop);

	/* Check property existence */
	if(index == -1) return;

	/* Update config property */
	update_config_prop(index, value);

	/* Open file */
	FILE *file = fopen("config.txt", "w+");

	/* Writing data */
	fprintf(file, "%s=%d\n", "WIDTH", config_screen_width);
	fprintf(file, "%s=%d\n", "HEIGHT", config_screen_height);
	fprintf(file, "%s=%s\n", "TITLE", config_screen_title);
	fprintf(file, "%s=%d\n", "FPS", config_screen_fps);

	/* Close file */
	fclose(file);

} 

/* Loading configurations from a file */ 
void load_config() {

	/* Helpers */ 
	int index; // index property
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
		index = -1;
		strcpy(value, "");

		/* Line splitting */
		istr = strtok(buffer, "=");

		/* Processing parts of a string */
		while(istr != NULL) {

			/* Writing a property value */
			if(index != -1)
				strcpy(value, istr);
			
			/* Check properties */
			else index = get_property_index(istr);

			/* Get the second part of a string */
			istr = strtok(NULL, "=");
		}

		/* Update config property */
		if(index != -1 && strcmp(value, ""))
			update_config_prop(index, value);

	}

	/* Close file */
	fclose(file);

}