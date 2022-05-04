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
	r_load_texture(resources, "intro", "assets/intro.png"); // intro

	r_load_texture(resources, "aya_icon", "assets/aya_icon.png"); // aya icon
	r_load_texture(resources, "aya_view", "assets/aya_view.png"); // aya view
	r_load_texture(resources, "aya_sprite", "assets/aya_sprite.png"); // aya sprite

	r_load_texture(resources, "sakuya_icon", "assets/sakuya_icon.png"); // sakuya icon
	r_load_texture(resources, "sakuya_view", "assets/sakuya_view.png"); // sakuya view
	r_load_texture(resources, "sakuya_sprite", "assets/sakuya_sprite.png"); // sakuya sprite

	r_load_texture_resize(resources, "location_1_icon", "assets/location_1.png", 256, 144); // location 1 icon
	r_load_texture(resources, "location_1_background", "assets/location_1.png"); // location 1 background
	r_load_texture(resources, "location_1_surface", "assets/location_1_surface.png"); // location 1 surface

	r_load_texture_resize(resources, "location_2_icon", "assets/location_2.png", 256, 144); // location 2 icon
	r_load_texture(resources, "location_2_background", "assets/location_2.png"); // location 2 background
	r_load_texture(resources, "location_2_surface", "assets/location_2_surface.png"); // location 2 surface

}

/* Unload all resources */ 
void unload_resources(Resources *resources) {

	/* Unload textures */
	r_unload_texture(resources, "intro"); // intro

	r_unload_texture(resources, "aya_icon"); // aya icon
	r_unload_texture(resources, "aya_view"); // aya view
	r_unload_texture(resources, "aya_sprite"); // aya sprite

	r_unload_texture(resources, "sakuya_icon"); // sakuya icon
	r_unload_texture(resources, "sakuya_view"); // sakuya view
	r_unload_texture(resources, "sakuya_sprite"); // sakuya sprite

	r_unload_texture(resources, "location_1_icon"); // location 1 icon
	r_unload_texture(resources, "location_1_background"); // location 1 background
	r_unload_texture(resources, "location_1_surface"); // location 1 surface

	r_unload_texture(resources, "location_2_icon"); // location 2 icon
	r_unload_texture(resources, "location_2_background"); // location 2 background
	r_unload_texture(resources, "location_2_surface"); // location 2 surface

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
