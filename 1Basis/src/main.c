// Стандартные библиотеки
#include <stdio.h>

// Внешние библиотеки
#include <SDL.h>

// Структура Игрок
typedef struct Player {
    int x, y;   // позиция
    short life; // очки жизни
    char *name; // имя
} Player;

// Обработка событий
int game_events(Player *player) {
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
        player->x -= 10;
    // Движение вправо
    if(state[SDL_SCANCODE_RIGHT])
        player->x += 10;
    // Движение вверх
    if(state[SDL_SCANCODE_UP])
        player->y -= 10;
    // Движение вниз
    if(state[SDL_SCANCODE_DOWN])
        player->y += 10;

    return quit;
}

// Отрисовка
int game_render(SDL_Renderer *rndr, Player *player) {

    // Задать цвет отрисовки (синий)
    SDL_SetRenderDrawColor(rndr,
        60,  // red
        60,  // green
        60,  // blue
        255  // alpha
    );

    // Очистка экрана (из-за цвета отрисовки будет синим)
    SDL_RenderClear(rndr);

    // Задать цвет отрисовки (белый)
    SDL_SetRenderDrawColor(rndr, 255, 255, 255, 255);

    // Создание и отрисовка прямогульника
    SDL_Rect rect = {
        player->x, // x
        player->y, // y
        200, // width
        200  // height
    };
    SDL_RenderFillRect(rndr, &rect);

    // Отрисовка объектов на окне
    SDL_RenderPresent(rndr);

    return 0;
}

// Старт
int main(int argc, char *argv[]) {

    // Объявление констант
    const int FPS = 30;
    const int DELAY = 1000 / FPS;

    // Объявление переменных
    int quit = 0; // игровой цикл

    SDL_Window *window; // Объявление окна
    SDL_Renderer *rndr; // Объявление визуализатора

    Player player;
    player.x = 220;
    player.y = 140;

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
    rndr = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    /* Игровой цикл */
    while(!quit) {

        /* Обработка событий */
        quit = game_events(&player);

        /* Отрисовка */
        game_render(rndr, &player);

        /* FPS */
        SDL_Delay(DELAY);
    }

    // Закрытие и уничтожение окна
    SDL_DestroyWindow(window);
    // Закрытие и уничтожение визуализатора
    SDL_DestroyRenderer(rndr);

    // Выход из SDL2
    SDL_Quit();

    return 0;
}