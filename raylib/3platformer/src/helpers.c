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