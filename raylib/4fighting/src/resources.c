/* Include libraries */
#include <stdio.h>
#include <string.h>

/* Include libraries */
#include <raylib.h>

/* Include files */
#include "resources.h"

/* Load all resources */ 
void load_resources(Resources *resources) {
	resources->count_textures = 0; // count textures

	/* Load textures */
	r_load_texture(resources, "logo", "assets/logo.png"); // logo

}

/* Unload all resources */ 
void unload_resources(Resources *resources) {

	/* Unload textures */
	r_unload_texture(resources, "logo"); // logo

}

/* Load texture */
void r_load_texture(Resources *resources, char *name, char *src) {
	if(resources->count_textures >= MAX_TEXTURES) return;
	resources->textures[resources->count_textures++] = load_texture(name, src);
}

/* Load texture with resize */
void r_load_texture_resize(Resources *resources, char *name, char *src, int w, int h) {
	if(resources->count_textures >= MAX_TEXTURES) return;
	resources->textures[resources->count_textures++] = load_texture_resize(name, src, w, h);
}

/* Get texture */
MyTexture r_get_texture(Resources *resources, char *name) {
	for(int i = 0; i < resources->count_textures; i++)
		if(!strcmp(resources->textures[i].name, name))
			return resources->textures[i];
}

/* Unload texture */
void r_unload_texture(Resources *resources, char *name) {
	for(int i = 0; i < resources->count_textures; i++)
		if(!strcmp(resources->textures[i].name, name))
			return unload_texture(&resources->textures[i]);
} 
