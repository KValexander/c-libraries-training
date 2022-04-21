#ifndef HELPERS_H_
#define HELPERS_H_

/* Include libraries */
#include <raylib.h> 

/* Struct Rect */
typedef struct {
	float x, y, w, h;
} Rect;

/* Load texture */ 
extern void load_texture(Texture2D *texture,
					char *src, int w,
					int h); // load texture

/* Rect collision */ 
extern int collide_2d(float x1, float y1,
					  float x2, float y2,
					  float wt1, float ht1,
					  float wt2, float ht2); // collision

/* Sides collision */
extern int sides_collision(float x1, float y1,
						   float x2, float y2,
						   float wt1, float ht1,
						   float wt2, float ht2); // collision

#endif