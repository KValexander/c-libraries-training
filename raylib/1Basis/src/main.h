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
typedef enum GameScreen {
	SCREEN_LIVES=0,
	SCREEN_GAME,
	SCREEN_GAMEOVER
} GameScreen;

// Структура Текстуры
typedef struct {
	Texture2D fire; // огонь
	Texture2D star; // звезда
	Texture2D player; // игрок
	Texture2D platform; // платформа
} Textures;

// Структура Прямоугольник
typedef struct {
	int x, y, w, h;
} Rect;

// Структура Позиция
typedef struct {
	int x, y;
} Position;

// Структура Игрок
typedef struct {
	Rect rect; // данные
	float dx, dy; // скорость
	int is_dead; // состояние смерти
	int on_platform; // состояние коллизии
} Player;

// Структура Игра
typedef struct {
	Textures textures; // структура Текстуры
	Player player; // структура Игрок
	Position camera; // структура Камера

	Rect stars[NUM_STARS]; // массив звёзд
	Rect platforms[NUM_PLATFORMS]; // массив платформ

	GameScreen current_screen; // игровые экраны

	int frame; // время
} Game;

// Прототипы функций (основная структура)
// extern не обязателен, просто показать, что это прототипы
extern void init(Game *game);
extern void events(Game *game);
extern void update(Game *game);
extern void collisions(Game *game);
extern void render(Game *game);
extern void deinit(Game *game);

#endif