#ifndef COMMON_H_
#define COMMON_H_

/* Common contsants */
#define WIDTH 	960 // window screen
#define HEIGHT 	540 // window height
#define FPS 	60  // FPS
#define GRAVITY .4f // gravity

/* Common structs */ 
/* Struct Position */
typedef struct Position {
	float x, y;
} Position;

/* Struct Rect */
typedef struct Rect {
	float x, y, w, h;
} Rect;

#endif