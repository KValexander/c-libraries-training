#ifndef sdl2_main_h
#define sdl2_main_h

// Экраны
#define STATUS_LIVES 0
#define STATUS_GAME 1
#define STATUS_GAMEOVER 2

#define NUM_STARS 100

// Внешние библиотеки
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

// Структура Текстуры
typedef struct {
    SDL_Texture *player_frames[2];
    SDL_Texture *ledge;
    SDL_Texture *star;
    SDL_Texture *fire;
    SDL_Texture *label, *label2;
} Textures;

// Структура Игрок
typedef struct {
    float x, y;     // позиция
    int w, h;       // ширина и высота
    float dx, dy;   // скорость
    short lives;    // количество жизней
    char *name;     // имя
    int is_dead;    // состояние смерти
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

    float scroll_x; // камера
    
    Player player; // структура Игрок
    Star stars[NUM_STARS]; // массив структур Звезда
    Ledge ledges[100]; // массив структур Уступ

    int time; // время
    int death_countdown; // обратный отсчёт до смерти
    int status; // состояние

    SDL_Renderer *rndr; // визуализатор
    TTF_Font *font; // шрифт
    SDL_Joystick * joystick; // джойстик

    int label_w, label_h, label_w2, label_h2;

} GameState;

// Прототипы функций
void load_game(GameState *game);
int game_events();
void game_update(GameState *game);
void game_collision(GameState *game);
void game_render(GameState *game);

#endif
