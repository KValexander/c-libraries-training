// Защита от повторного включения
#ifndef raylib_main_h
#define raylib_main_h

// Размеры экрана окна
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define FPS 60 // FPS

#define GRAVITY 0.35f // гравитация

#define NUM_STARS 100 // кол-во звёзд
#define NUM_PLATFORMS 100 // кол-во платформ

// Игровые экраны
typedef enum {
	SCREEN_LIVES=0,
	SCREEN_GAME,
	SCREEN_GAMEOVER
} GameScreen;

// Структура Текстуры
typedef struct {
	Texture2D fire; // огонь
	Texture2D star; // звезда
	Texture2D player[2]; // игрок
	Texture2D platform; // платформа
} Textures;

// Структура Позиция
typedef struct {
	int x, y;
} Position;

// Структура Прямоугольник
typedef struct {
	int x, y, w, h;
} Rect;

// Структура Надпись
typedef struct {
	Vector2 pos;
	Vector2 size;
	char text[128];
} Label;

// Структура Игрок
typedef struct {
	Rect rect; // данные
	float dx, dy; // скорость
	int lives; // количество жизней
	int is_dead; // состояние смерти
	int on_platform; // состояние коллизии
	int current_frame; // текущий фрейм
} Player;

// Структура Игра
typedef struct {
	Textures textures; // структура Текстуры
	Player player; // структура Игрок
	Position camera; // структура Камера

	Font font; // шрифт

	Rect stars[NUM_STARS]; // массив звёзд
	Rect platforms[NUM_PLATFORMS]; // массив платформ

	GameScreen current_screen; // игровые экраны

	Label labels[2]; // массив надписей

	int frame; // время
	int death_countdown; // отсчёт смерти
} Game;

// Прототипы функций (основная структура)
// extern не обязателен, просто показать, что это прототипы
extern void load_texture(Texture2D *texture, char src[], int w, int h);
extern void init_reset(Game *game);
extern void init(Game *game);

extern void events(Game *game);

extern void update_lives(Game *game);
extern void update_game(Game *game);
extern void update_game_over(Game *game);
extern void update(Game *game);

extern void collisions(Game *game);

extern void render_lives(Game *game);
extern void render_game(Game *game);
extern void render_game_over(Game *game);
extern void render(Game *game);

extern void deinit(Game *game);

#endif