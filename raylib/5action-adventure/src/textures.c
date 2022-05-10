/* Include libraries */
#include <stdio.h>
#include <string.h>

/* Include files */
#include "textures.h"

/* Textures */ 
/* Load textures */
void load_textures(Textures *textures) {
    textures->count_textures = 0; // count textures

    /* Create texture map */
    create_texture(textures, "map", -1, "assets/graphics/tilemap/ground.png");

    /* Create texture player */
    create_texture(textures, "player", -1, "assets/graphics/player/player.png");

    /* Create texture grass */ 
    create_texture(textures, "grass0", 21, "assets/graphics/grass/grass_1.png");
    create_texture(textures, "grass1", 22, "assets/graphics/grass/grass_2.png");
    create_texture(textures, "grass2", 23, "assets/graphics/grass/grass_3.png");

    /* Create texture objects */ 
    create_texture(textures, "object0", 0, "assets/graphics/objects/0.png");
    create_texture(textures, "object1", 1, "assets/graphics/objects/01.png");
    create_texture(textures, "object2", 2, "assets/graphics/objects/02.png");
    create_texture(textures, "object3", 3, "assets/graphics/objects/03.png");
    create_texture(textures, "object4", 4, "assets/graphics/objects/04.png");
    create_texture(textures, "object5", 5, "assets/graphics/objects/05.png");
    create_texture(textures, "object6", 6, "assets/graphics/objects/06.png");
    create_texture(textures, "object7", 7, "assets/graphics/objects/07.png");
    create_texture(textures, "object8", 8, "assets/graphics/objects/08.png");
    create_texture(textures, "object9", 9, "assets/graphics/objects/09.png");
    create_texture(textures, "object10", 10, "assets/graphics/objects/10.png");
    create_texture(textures, "object11", 11, "assets/graphics/objects/11.png");
    create_texture(textures, "object12", 12, "assets/graphics/objects/12.png");
    create_texture(textures, "object13", 13, "assets/graphics/objects/13.png");
    create_texture(textures, "object14", 14, "assets/graphics/objects/14.png");
    create_texture(textures, "object15", 15, "assets/graphics/objects/15.png");
    create_texture(textures, "object16", 16, "assets/graphics/objects/16.png");
    create_texture(textures, "object17", 17, "assets/graphics/objects/17.png");
    create_texture(textures, "object18", 18, "assets/graphics/objects/18.png");
    create_texture(textures, "object19", 19, "assets/graphics/objects/19.png");
    create_texture(textures, "object20", 20, "assets/graphics/objects/20.png");

}

/* Unload textures */
void unload_textures(Textures *textures) {

    /* Unload map */
    unload_texture(textures, "map");

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
void create_texture(Textures *textures, char *name, int id, char *src) {
    if(textures->count_textures >= MAX_TEXTURES) return;
    textures->textures[textures->count_textures++] = create_my_texture(name, id, src);
}

/* Create texture with resize */
void create_texture_resize(Textures *textures, char *name, int id, char *src, int w, int h) {
    if(textures->count_textures >= MAX_TEXTURES) return;
    textures->textures[textures->count_textures++] = create_my_texture_resize(name, id, src, w, h);
}

/* Get texture */
MyTexture get_texture(Textures *textures, char *name) {
    for(int i = 0; i < textures->count_textures; i++)
        if(!strcmp(textures->textures[i].name, name))
            return textures->textures[i];
}

/* Get texture by id */ 
MyTexture get_texture_by_id(Textures *textures, int id) {
    for(int i = 0; i < textures->count_textures; i++)
        if(textures->textures[i].id == id)
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


/* Unload texture by id */
void unload_texture_by_id(Textures *textures, int id) {
    for(int i = 0; i < textures->count_textures; i++)
        if(textures->textures[i].id == id)
            return unload_my_texture(&textures->textures[i]);
} 

/* Unload texture by index */
void unload_texture_by_index(Textures *textures, int index) {
    for(int i = 0; i < textures->count_textures; i++)
        if(index == i) return unload_my_texture(&textures->textures[i]);
} 

/* MyTexture */ 
/* Create MyTexture */
MyTexture create_my_texture(char *name, int id, char *src) {
   
    /* Structure declaration */ 
    MyTexture s_texture;

    /* Naming */
    strcpy(s_texture.name, name);

    /* ID */
    s_texture.id = id;
    
    /* Load texture */ 
    s_texture.texture = LoadTexture(src);

    /* Get texture size */ 
    s_texture.w = s_texture.texture.width;
    s_texture.h = s_texture.texture.height;

    /* Return texture */ 
    return s_texture;

}

/* Load MyTexture with resize */
MyTexture create_my_texture_resize(char *name, int id, char *src, int w, int h) {
    
    /* Structure declaration */ 
    MyTexture s_texture;

    /* Naming */
    strcpy(s_texture.name, name);

    /* ID */
    s_texture.id = id;
    
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