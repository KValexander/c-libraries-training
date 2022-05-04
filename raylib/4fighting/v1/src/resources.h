#ifndef RESOURCES_H_
#define RESOURCES_H_

/* Constants */
#define MAX_TEXTURES 100

/* Include files */
#include "resources/texture.h"

/* Struct Resources */
typedef struct Resources {

	/* Textures */ 
	int count_textures; // count textures
	MyTexture textures[MAX_TEXTURES]; // texture array

} Resources;

/* Prototypes */
extern void load_resources(Resources *resources); // load all resources
extern void unload_resources(Resources *resources); // unload all resources

/* Textures */
extern void r_load_texture(Resources *resources, char *name, char *str);
extern void r_load_texture_resize(Resources *resources, char *name, char *str, int w, int h);
extern MyTexture r_get_texture(Resources *resources, char *name);
extern void r_unload_texture(Resources *resources, char *name);

#endif