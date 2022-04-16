#ifndef raylib_assets_h
#define raylib_assets_h

// Struct Fonts
typedef struct {

} Fonts;

// Struct Sounds
typedef struct {

} Sounds;

// Struct Textures
typedef struct {

} Textures;

// Struct Assets
typedef struct {
	Fonts fonts; // struct Fonts
	Sounds sounds; // struct Sounds
	Textures textures; // struct Textures
} Assets;

// Prototypes
extern void assets_init();
extern void assets_fonts_init();
extern void assets_sounds_init();
extern void assets_textures_init();
extern void assets_deinit();

#endif