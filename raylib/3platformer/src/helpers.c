/* Include libraries */
#include <stdio.h>
#include <dirent.h>
#include <string.h>

/* Include libraries */
#include <raylib.h> 

/* Include files */
#include "helpers.h" 

/* Load texture */
void load_texture(Texture2D *texture, char *src, int w, int h) {
    Image image = LoadImage(src); // load image
    ImageResize(&image, w, h); // image resize
    *texture = LoadTextureFromImage(image); // load texture
    UnloadImage(image); // unload image
}

/* Rect collision */
int collide_2d(float x1, float y1, float x2, float y2, float wt1, float ht1, float wt2, float ht2) {
    return (!((x1 > (x2+wt2)) || (x2 > (x1+wt1)) || (y1 > (y2+ht2)) || (y2 > (y1+ht1))));
}

/* Sides collision */
/*
    1 - UP
    2 - RIGHT
    3 - DOWN
    4 - LEFT
*/ 
int sides_collision(float x1, float y1, float x2, float y2, float w1, float h1, float w2, float h2) {

    /* Up */
    if(x1 + w1 > x2 && x1 < x2 + w2)
        if(y1 + h1 >= y2 && y1 <= y2)
            return 1;

    /* Down */
    else if (x1 + w1 / 2 > x2 && x1 + w1 / 2 < x2 + w2)
        if (y1 < y2 + h2 && y1 > y2)
            return 3;

    /* Sides */
    if(y1 + h1 > y2 && y1 < y2 + h2) {
        
        /* Left */
        if(x1 + w1 > x2 && x1 < x2)
            return 4;

        /* Right */
        else if(x1 < x2 + w2 && x1 > x2 + w2)
            return 2;

    }

    return 0;

}
