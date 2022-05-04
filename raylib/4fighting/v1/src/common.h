#ifndef COMMON_H_
#define COMMON_H_

/* Constants */
#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 540
#define FPS 60

/* Enum AnimationState */
typedef enum AnimationState {
	ANIMATION_IDLE = 0,
	ANIMATION_MOVE = 2,
	ANIMATION_JUMP,
	ANIMATION_DOWN,
	ANIMATION_ATTACK,
} AnimationState;

/* Enum AnimationDirection */ 
typedef enum AnimationDirection {
	ANIMATION_RIGHT = 0,
	ANIMATION_LEFT
} AnimationDirection;

/* Struct Position */
typedef struct Position {
	int x, y;
} Position;

/* Struct Rect */
typedef struct Rect {
	int x, y, w, h;
} Rect;

/* Prototypes */

/* Check collision */ 
extern int check_collision(float x1, float y1,
					  	   float x2, float y2,
					  	   float w1, float h1,
					 	   float w2, float h2);



#endif