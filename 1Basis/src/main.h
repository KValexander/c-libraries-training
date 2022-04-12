#ifndef sdl2_main_h
#define sdl2_main_h

#define STATUS_LIVES 0
#define STATUS_GAME 1
#define STATUS_GAMEOVER 2

// Внешние библиотеки
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

// Структура Текстуры
typedef struct {
    SDL_Texture *player_frames[2];
    SDL_Texture *ledge;
    SDL_Texture *star;
    SDL_Texture *label;
} Textures;

// Структура Игрок
typedef struct {
    float x, y;     // позиция
    int w, h;       // ширина и высота
    float dx, dy;   // скорость
    short life;     // очки жизни
    char *name;     // имя
    int on_ledge;   // проверка коллизии
    int anim_frame; // фреймы анимации
    int facing_left; // поворот игрока
    int slowing_down; // замедление
} Player;

// Структура Звезда
typedef struct Star{
    int x, y;
} Star;

// Структура Уступ
typedef struct {
    int x, y, w, h;
} Ledge;

// Структура Состояние игры
typedef struct {
    Textures textures;  // структура Текстуры
    
    Player player;      // структура Игрок
    Star stars[100];    // массив структур Звезда
    Ledge ledges[100];  // массив структур Уступ

    int time; // время
    int status; // состояние

    SDL_Renderer *rndr; // визуализатор
    TTF_Font *font; // шрифт

    int label_w, label_h;

} GameState;

// Прототипы функций
void load_game(GameState *game);
int game_events();
void game_update(GameState *game);
void game_collision(GameState *game);
void game_render(GameState *game);

#endif
