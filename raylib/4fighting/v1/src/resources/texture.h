#ifndef TEXTURE_H_
#define TEXTURE_H_

/* Include libraries */
#include <raylib.h>

/* Struct Texture */
typedef struct MyTexture {
	char name[255];
	int w, h;
	Texture2D texture;
} MyTexture;

/* Prototypes */
extern MyTexture load_texture(char name[255], char *src); // load texture
extern MyTexture load_texture_resize(char name[255], char *src, int w, int h); // load texture with resize
extern void unload_texture(MyTexture *texture);

#endif