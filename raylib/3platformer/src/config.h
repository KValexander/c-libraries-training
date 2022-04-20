#ifndef CONFIG_H_
#define CONFIG_H_

/* Property List */ 
static char *config_properties[] = {
		"WIDTH", 	// 0
		"HEIGHT", 	// 1
		"FPS", 		// 2
		"TITLE" 	// 3
	};
/* Count of elements in the array */ 
static int config_count_prop = sizeof(config_properties) / sizeof(config_properties[0]);

/* Standard configurations */
static int config_screen_width  = 300;
static int config_screen_height = 300;
static int config_screen_fps 	= 30;
static char config_screen_title[30] = "Project";

/* Prototypes */
extern void load_config(); // loading configuration
extern int get_property_index(char *prop); // get property index
extern void update_config_prop(int index, char *value); // change config property
extern void change_config_prop(char *prop, char *value); // change config property

extern int get_screen_width(); // get screen width
extern int get_screen_height(); // get screen height
extern int get_screen_fps(); // get screen fps
extern char *get_screen_title(); // get screen title

#endif