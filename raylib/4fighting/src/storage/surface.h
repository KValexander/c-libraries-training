#ifndef SURFACE_H_
#define SURFACE_H_

/* Include files */
#include "common.h"
#include "resources/texture.h"

/* Struct Surface */
typedef struct Surface {
	int x, y, w, h; // position
	int collision; // state collision

	MyTexture texture; // texture
} Surface;

/* Prototypes */
extern Surface create_surface(int x, int y, int collision, MyTexture texture);

/* Draw surface */
extern void surface_draw(Surface *surface);

#endif