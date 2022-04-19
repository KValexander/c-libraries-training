#ifndef CONFIG_H_
#define CONFIG_H_

/* Standard configurations */
static int config_screen_width  = 300;
static int config_screen_height = 300;
static int config_screen_fps 	= 30;
static char config_screen_title[30] = "Project";

/* Prototypes */
extern void load_config(); // loading configuration

extern int get_screen_width(); // get screen width
extern int get_screen_height(); // get screen height
extern int get_screen_fps(); // get screen fps
extern char *get_screen_title(); // get screen title

#endif