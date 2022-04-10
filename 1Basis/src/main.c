// Стандартные библиотеки
#include <stdio.h>
// Внешние библиотеки
#include <SDL.h>
#include <SDL_image.h>

// Структура Игрок
typedef struct {
    int x, y;   // позиция
    int width;  // ширина
    int height; // высота
    short life; // очки жизни
    char *name; // имя
    SDL_Texture *texture; // Текстура
} Player;

// Структура Состояние игры
typedef struct {
    Player player;      // структура Игрок
    SDL_Renderer *rndr; // визуализатор
} GameState;

// Обработка событий
int game_events(GameState *game_state) {
    SDL_Event event;
    int quit = 0;

    // Цикл обработки событий
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            // Выход из приложения
            case SDL_QUIT: quit = 1; break;
        }
    }

    // Обработка нажатий на клавиши
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    // Движение влево
    if(state[SDL_SCANCODE_LEFT])
        game_state->player.x -= 10;
    // Движение вправо
    if(state[SDL_SCANCODE_RIGHT])
        game_state->player.x += 10;
    // Движение вверх
    if(state[SDL_SCANCODE_UP])
        game_state->player.y -= 10;
    // Движение вниз
    if(state[SDL_SCANCODE_DOWN])
        game_state->player.y += 10;

    return quit;
}

// Отрисовка
int game_render(GameState *game_state) {

    // Задать цвет отрисовки (синий)
    SDL_SetRenderDrawColor(game_state->rndr,
        150,  // red
        150,  // green
        150,  // blue
        255  // alpha
    );

    // Очистка экрана (из-за цвета отрисовки будет синим)
    SDL_RenderClear(game_state->rndr);

    // Задать цвет отрисовки (белый)
    SDL_SetRenderDrawColor(game_state->rndr, 255, 255, 255, 255);

    // Создание и отрисовка прямогульника
    // SDL_Rect rect = {
    //     game_state->player.x, // x
    //     game_state->player.y, // y
    //     game_state->player.width, // width
    //     game_state->player.height // height
    // };
    // SDL_RenderFillRect(game_state->rndr, &rect);

    // Отрисовка текстуры игрока
    SDL_Rect player_rect = {
        game_state->player.x, // x
        game_state->player.y, // y
        game_state->player.width, // width
        game_state->player.height // height
    };
    SDL_RenderCopy(
        game_state->rndr,
        game_state->player.texture,
        NULL,
        &player_rect
    );


    // Отрисовка объектов на окне
    SDL_RenderPresent(game_state->rndr);

    return 0;
}

// Старт
int main(int argc, char *argv[]) {

    // Объявление констант
    const int FPS = 30;
    const int DELAY = 1000 / FPS;

    // Объявление переменных
    int quit = 0; // игровой цикл

    SDL_Window *window = NULL; // Объявление окна
    SDL_Surface *surface = NULL; // Поверхность

    GameState game_state; // Структура Состояние игры
    game_state.player.x = 320-50;
    game_state.player.y = 240-45;
    game_state.player.width = 100;
    game_state.player.height = 95;

    // Инициализация SDL2
    SDL_Init(SDL_INIT_VIDEO);

    // Создание окна
    window = SDL_CreateWindow(
        "SDL",                   // название окна
        SDL_WINDOWPOS_UNDEFINED, // стартовая pos x
        SDL_WINDOWPOS_UNDEFINED, // стартовая pos y
        640,                     // ширина
        480,                     // высота
        0                        // флаги
    );
    // Создание визуализатора
    game_state.rndr = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Загрузка изображения
    surface = IMG_Load("assets/star.png");
    // Создание текстуры
    game_state.player.texture = SDL_CreateTextureFromSurface(game_state.rndr, surface);
    // Очистка поверхности
    SDL_FreeSurface(surface);

    /* Игровой цикл */
    while(!quit) {

        /* Обработка событий */
        quit = game_events(&game_state);

        /* Отрисовка */
        game_render(&game_state);

        /* FPS */
        SDL_Delay(DELAY);
    }

    // Уничтожение текстуры
    SDL_DestroyTexture(game_state.player.texture);

    // Закрытие и уничтожение окна
    SDL_DestroyWindow(window);
    // Закрытие и уничтожение визуализатора
    SDL_DestroyRenderer(game_state.rndr);

    // Выход из SDL2
    SDL_Quit();

    return 0;
}