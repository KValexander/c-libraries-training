/* Include libraries */
#include <stdio.h>
#include <string.h>

/* Include files */
#include "textures.h"

/* Textures */ 
/* Load textures */
void load_textures(Textures *textures) {
    textures->count_textures = 0; // count textures

    /* Create texture player */
    create_texture(textures, "player", "assets/graphics/test/player.png");
    create_texture(textures, "rock", "assets/graphics/test/rock.png");

    /* Create texture grass */ 
    create_texture(textures, "grass0", "assets/graphics/grass/grass_1.png");
    create_texture(textures, "grass1", "assets/graphics/grass/grass_2.png");
    create_texture(textures, "grass2", "assets/graphics/grass/grass_3.png");

    /* Create texture objects */ 
    create_texture(textures, "object0", "assets/graphics/objects/0.png");
    create_texture(textures, "object1", "assets/graphics/objects/1.png");
    create_texture(textures, "object2", "assets/graphics/objects/2.png");
    create_texture(textures, "object3", "assets/graphics/objects/3.png");
    create_texture(textures, "object4", "assets/graphics/objects/4.png");
    create_texture(textures, "object5", "assets/graphics/objects/5.png");
    create_texture(textures, "object6", "assets/graphics/objects/6.png");
    create_texture(textures, "object7", "assets/graphics/objects/7.png");
    create_texture(textures, "object8", "assets/graphics/objects/8.png");
    create_texture(textures, "object9", "assets/graphics/objects/9.png");
    create_texture(textures, "object10", "assets/graphics/objects/10.png");
    create_texture(textures, "object11", "assets/graphics/objects/11.png");
    create_texture(textures, "object12", "assets/graphics/objects/12.png");
    create_texture(textures, "object13", "assets/graphics/objects/13.png");
    create_texture(textures, "object14", "assets/graphics/objects/14.png");
    create_texture(textures, "object15", "assets/graphics/objects/15.png");
    create_texture(textures, "object16", "assets/graphics/objects/16.png");
    create_texture(textures, "object17", "assets/graphics/objects/17.png");
    create_texture(textures, "object18", "assets/graphics/objects/18.png");
    create_texture(textures, "object19", "assets/graphics/objects/19.png");
    create_texture(textures, "object20", "assets/graphics/objects/20.png");

}

/* Unload textures */
void unload_textures(Textures *textures) {

    /* Unload player */ 
    unload_texture(textures, "player");
    unload_texture(textures, "rock");

    /* Unload grass */ 
    unload_texture(textures, "grass0");
    unload_texture(textures, "grass1");
    unload_texture(textures, "grass2");

    /* Unload objects */ 
    unload_texture(textures, "object0");
    unload_texture(textures, "object1");
    unload_texture(textures, "object2");
    unload_texture(textures, "object3");
    unload_texture(textures, "object4");
    unload_texture(textures, "object5");
    unload_texture(textures, "object6");
    unload_texture(textures, "object7");
    unload_texture(textures, "object8");
    unload_texture(textures, "object9");
    unload_texture(textures, "object10");
    unload_texture(textures, "object11");
    unload_texture(textures, "object12");
    unload_texture(textures, "object13");
    unload_texture(textures, "object14");
    unload_texture(textures, "object15");
    unload_texture(textures, "object16");
    unload_texture(textures, "object17");
    unload_texture(textures, "object18");
    unload_texture(textures, "object19");
    unload_texture(textures, "object20");


}


/* Create texture */
void create_texture(Textures *textures, char *name, char *src) {
    if(textures->count_textures >= MAX_TEXTURES) return;
    textures->textures[textures->count_textures++] = create_my_texture(name, src);
}

/* Create texture with resize */
void create_texture_resize(Textures *textures, char *name, char *src, int w, int h) {
    if(textures->count_textures >= MAX_TEXTURES) return;
    textures->textures[textures->count_textures++] = create_my_texture_resize(name, src, w, h);
}

/* Get texture */
MyTexture get_texture(Textures *textures, char *name) {
    for(int i = 0; i < textures->count_textures; i++)
        if(!strcmp(textures->textures[i].name, name))
            return textures->textures[i];
}

/* Get texture by index */ 
MyTexture get_texture_by_index(Textures *textures, int index) {
    for(int i = 0; i < textures->count_textures; i++)
        if(index == i) return textures->textures[i];
}

/* Unload texture */
void unload_texture(Textures *textures, char *name) {
    for(int i = 0; i < textures->count_textures; i++)
        if(!strcmp(textures->textures[i].name, name))
            return unload_my_texture(&textures->textures[i]);
} 

/* Unload texture by index */
void unload_texture_by_index(Textures *textures, int index) {
    for(int i = 0; i < textures->count_textures; i++)
        if(index == i) return unload_my_texture(&textures->textures[i]);
} 

/* MyTexture */ 
/* Create MyTexture */
MyTexture create_my_texture(char *name, char *src) {
   
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

/* Load MyTexture with resize */
MyTexture create_my_texture_resize(char *name, char *src, int w, int h) {
    
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

/* Unload MyTexture */
void unload_my_texture(MyTexture *texture) {
    UnloadTexture(texture->texture);
    texture->w = 0;
    texture->h = 0;
}