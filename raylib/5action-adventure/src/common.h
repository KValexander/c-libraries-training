#ifndef COMMON_H_
#define COMMON_H_

/* Common contsants */
#define WIDTH 	960 // window screen
#define HEIGHT 	540 // window height
#define FPS 	60  // FPS

/* MAP */
#define TILESIZE 64 // tile size
#define ROWS 20 	// rows
#define COLUMNS 20 	// columns

/* WORLD MAP */
/*
	0 - void
	1 - let
	9 - player
*/ 
static const int WORLD_MAP[ROWS][COLUMNS] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};
 
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

/* Side collision
	1 - top
	2 - right
	3 - bottom
	4 - left
*/ 
static int side_collision(float x1, float y1, float x2, float y2, float w1, float h1, float w2, float h2) {
	int side = 0;

	/* TOP */
	if(x1 + w1 > x2 && x1 < x2 + w2)
		if(y1 + h1 > y2 && y1 < y2)
			side = 1;

	/* BOTTOM */
	else if(x1 + w1 / 2 > x2 && x1 + w1 / 2 < x2 + w2)
		if(y1 < y2 + h2 && y1 > y2)
			side = 3;

	/* SIDES */
	if(y1 + h2 > y2 && y1 < y2 + h2) {

		/* RIGHT */
		if(x1 < x2 + w2 && x1 + w1 > x2 + w2)
			side = 2;

		/* LEFT */
		else if(x1 + w1 > x2 && x1 < x2)
			side = 4;

	}

	/* Return side */
	return side; 
}

#endif