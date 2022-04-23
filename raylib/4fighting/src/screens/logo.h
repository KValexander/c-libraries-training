#ifndef LOGO_H_
#define LOGO_H_

/* Struct intro */ 
typedef struct Intro {
	int w, h; // single frame size

	/* Animation */ 
	int line_frame; // current line of frames
	int current_frame; // current frame on line
	int max_lines; // max lines
	int max_on_line; // max frame on line
} Intro;

/* Prototypes */
/* Entry points */ 
extern void logo_entry(Game *game); // logo screen entry
extern void logo_update(Game *game); // logo screen update
extern void logo_render(Game *game); // logo screen render

#endif