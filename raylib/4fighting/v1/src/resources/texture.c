/* Include libraries */
#include <stdio.h>
#include <string.h>

/* Include libraries */
#include <raylib.h>

/* Include files */
#include "texture.h"

/* Load texture */
MyTexture load_texture(char *name, char *src) {
   
    /* Structure declaration */ 
    MyTexture s_texture;

    /* Naming */
    strcpy(s_texture.name, name);
    
    /* Load texture */ 
    s_texture.texture = LoadTexture(src);

    /* Get texture size */ 
    s_texture.w = s_texture.texture.width;
    s_texture.h = s_texture.texture.height;

    /* Return texture */ 
    return s_texture;

}

/* Load texture with resize */
MyTexture load_texture_resize(char name[255], char *src, int w, int h) {
    
    /* Structure declaration */ 
    MyTexture s_texture;

    /* Naming */
    strcpy(s_texture.name, name);
    
    /* Load texture */ 
    Image image = LoadImage(src); // load image
    ImageResize(&image, w, h); // image resize
    s_texture.texture = LoadTextureFromImage(image); // load texture
    UnloadImage(image); // unload image

    /* Get texture size */ 
    s_texture.w = s_texture.texture.width;
    s_texture.h = s_texture.texture.height;

    /* Return texture */ 
    return s_texture;

}

/* Unload texture */
void unload_texture(MyTexture *texture) {
    UnloadTexture(texture->texture);
    texture->w = 0;
    texture->h = 0;
}