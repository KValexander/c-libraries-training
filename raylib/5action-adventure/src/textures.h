#ifndef TEXTURE_H_
#define TEXTURE_H_

/* Constants */
#define MAX_TEXTURES 1000

/* Include libraries */
#include <raylib.h>

/* Include files */
#include "common.h"

/* Struct MyTexture */
typedef struct MyTexture {
	char name[255];
	int id, w, h;
	Texture2D texture;
} MyTexture;

/* Struct Textures */ 
typedef struct Textures {
	int count_textures; // count textures
	MyTexture textures[MAX_TEXTURES]; // textures
} Textures;

/* Prototypes */
/* Textures */
/* Load textures */ 
extern void load_textures(Textures *textures);
/* Unload textures */ 
extern void unload_textures(Textures *textures);

/* Create texture */ 
extern void create_texture(Textures *textures, char *name, int id, char *src);
extern void create_texture_resize(Textures *textures, char *name, int id, char *src, int w, int h);

/* Get texture */ 
extern MyTexture get_texture(Textures *textures, char *name);
extern MyTexture get_texture_by_id(Textures *textures, int id);
extern MyTexture get_texture_by_index(Textures *textures, int index);

/* Unload texture */
extern void unload_texture(Textures *textures, char *name); 
extern void unload_texture_by_id(Textures *textures, int id); 
extern void unload_texture_by_index(Textures *textures, int index); 

/* MyTexture */
/* Create MyTexture */ 
extern MyTexture create_my_texture(char *name, int id, char *src); // create texture
extern MyTexture create_my_texture_resize(char *name, int id, char *src, int w, int h); // create texture with resize

/* Unload MyTexture */ 
extern void unload_my_texture(MyTexture *texture); // unload texture


#endif