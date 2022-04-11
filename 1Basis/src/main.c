// Стандартные библиотеки
#include <stdio.h>
#include <time.h>
// Внешние библиотеки
#include <SDL.h>
#include <SDL_image.h>

// Константы
#define GRAVITY 0.35f

// Структура Текстуры
typedef struct {
    SDL_Texture *player_frames[2];
    SDL_Texture *ledge;
    SDL_Texture *star;
} Textures;

// Структура Игрок
typedef struct {
    float x, y;   // позиция
    int w, h;   // ширина и высота
    float dx, dy; // скорость
    short life; // очки жизни
    char *name; // имя
    int on_ledge; // проверка коллизии
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

    SDL_Renderer *rndr; // визуализатор
} GameState;

// Загрузка игры
void load_game(GameState *game) {
    SDL_Surface *surface = NULL; // поверхность

    // Загрузка текстур
    // Звезда
    surface = IMG_Load("assets/star.png");
    if(surface == NULL) printf("Image not found");
    game->textures.star = SDL_CreateTextureFromSurface(game->rndr, surface);
    SDL_FreeSurface(surface); // очистка поверхности
    // Уступ
    surface = IMG_Load("assets/ledge.png");
    if(surface == NULL) printf("Image not found");
    game->textures.ledge = SDL_CreateTextureFromSurface(game->rndr, surface);
    SDL_FreeSurface(surface); // очистка поверхности
    // Фреймы игрока
        // Право
    surface = IMG_Load("assets/right.png");
    game->textures.player_frames[0] = SDL_CreateTextureFromSurface(game->rndr, surface);
    SDL_FreeSurface(surface); // очистка поверхности
        // Лево
    surface = IMG_Load("assets/left.png");
    game->textures.player_frames[1] = SDL_CreateTextureFromSurface(game->rndr, surface);
    SDL_FreeSurface(surface); // очистка поверхности

    // Инициализация игрока
    game->player.x = 320-24;
    game->player.y = 240-24;
    game->player.w = 48;
    game->player.h = 48;
    game->player.dx = 0;
    game->player.dy = 0;
    game->player.on_ledge = 0;

    // Инициализация звёзд
    for(int i = 0; i < 100; i++) {
        game->stars[i].x = rand() % 640;
        game->stars[i].y = rand() % 480;
    }

    // Инициализация уступов
    for(int i = 0; i < 100; i++) {
        game->ledges[i].w = 256;
        game->ledges[i].h = 64;
        game->ledges[i].x = i*256;
        game->ledges[i].y = 400;
    }
    game->ledges[99].x = 350;
    game->ledges[99].y = 200;
}

// Обработка событий
int game_events(GameState *game) {
    SDL_Event event;
    int quit = 0;

    // Цикл обработки событий
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT: quit = 1; break; // выход из приложения

            // Нажатия на клавиши
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                    case SDLK_UP:
                        if(game->player.on_ledge) {
                            game->player.dy = -12;
                            game->player.on_ledge = 0;
                        }
                    break;
                }
            break;

        }
    }

    // Обработка нажатий на клавиши
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    // Движение влево
    if(state[SDL_SCANCODE_LEFT])
        game->player.x -= 10;
    // Движение вправо
    else if(state[SDL_SCANCODE_RIGHT])
        game->player.x += 10;
    // // Движение вверх
    // if(state[SDL_SCANCODE_UP])
    //     game->player.y -= 10;
    // // Движение вниз
    // else if(state[SDL_SCANCODE_DOWN])
    //     game->player.y += 10;

    return quit;
}

void game_process(GameState *game) {
    Player *player = &game->player;
    player->y += player->dy;

    player->dy += GRAVITY;

}

// Обработка коллизий
void game_collision(GameState *game) {
    // Проверка коллизий на столкновение с уступами
    for(int i = 0; i < 100; i++) {

        // Получение данных
        float mx = game->player.x, my = game->player.y;
        float mw = game->player.w, mh = game->player.h;
        float bx = game->ledges[i].x, by = game->ledges[i].y;
        float bw = game->ledges[i].w, bh = game->ledges[i].h;

        // И пошла математика
        // Если задел
        if (my + mh > by && my < by + bh) {
            // Правая сторона
            if (mx < bx + bw && mx + mw > bx + bw) {
                game->player.x = bx + bw;
                mx = bx + bw;
            }
            // Левая сторона
            else if (mx + mw > bx && mx < bx) {
                game->player.x = bx - mw;
                mx = bx - mw;
            }
        }

        // Если задел 2
        if (mx + mw > bx && mx < bx + bw) {
            // Верхняя сторона
            if (my < by + bh && my > by) {
                game->player.y = by + bh;
                game->player.dy = 0;
                game->player.on_ledge = 1;
            }
            // Нижняя сторона
            else if (my + mh > by && my < by) {
                game->player.y = by - mh;
                game->player.dy = 0;
                game->player.on_ledge = 1;
            }
        }
    }
}


// Отрисовка
int game_render(GameState *game) {

    // Задать цвет отрисовки (серый)
    SDL_SetRenderDrawColor(game->rndr, 150, 150, 150, 255);

    // Очистка экрана (из-за цвета отрисовки будет серым)
    SDL_RenderClear(game->rndr);

    // Задать цвет отрисовки (белый)
    SDL_SetRenderDrawColor(game->rndr, 255, 255, 255, 255);

    // Создание и отрисовка уступов
    for(int i = 0; i < 100; i++) {
        SDL_Rect ledge_rect = {game->ledges[i].x, game->ledges[i].y, game->ledges[i].w, game->ledges[i].h};
        SDL_RenderCopy(game->rndr, game->textures.ledge, NULL, &ledge_rect); // отрисовка текстуры
    }

    // Создание и отрисовка текстуры игрока
    SDL_Rect player_rect = {game->player.x, game->player.y, game->player.w, game->player.h};
    // SDL_RenderFillRect(game->rndr, &rect); // отрисовка прямоугольника
    // SDL_RenderCopy(game->rndr, game->textures.player_frames[0], NULL, &player_rect); // отрисовка текстуры
    SDL_RenderCopyEx(game->rndr, game->textures.player_frames[0], NULL, &player_rect, 0, NULL, 0); // отрисовка текстуры

    // Создание и отрисовка звёзд
    // for(int i = 0; i < 100; i++) {
    //     SDL_Rect star_rect = {game->stars[i].x, game->stars[i].y, 32, 32};  // создание прямоугольника
    //     SDL_RenderCopy(game->rndr, game->textures.star, NULL, &star_rect); // отрисовка текстуры
    // }

    // Отрисовка объектов на окне
    SDL_RenderPresent(game->rndr);

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
    GameState game; // Структура Состояние игры

    // Инициализация 
    SDL_Init(SDL_INIT_VIDEO); // SDL2
    srand((int)time(NULL)); // случайные числа

    // Создание окна
    window = SDL_CreateWindow(  "SDL",                   // название окна
                                SDL_WINDOWPOS_UNDEFINED, // стартовая pos x
                                SDL_WINDOWPOS_UNDEFINED, // стартовая pos y
                                640,                     // ширина
                                480,                     // высота
                                0                        // флаги
                                );
    // Создание визуализатора
    game.rndr = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Загрузка данных
    load_game(&game);

    /* Игровой цикл */
    while(!quit) {

        /* Обработка событий */
        quit = game_events(&game);

        game_process(&game);

        /* Обработка коллизий */
        game_collision(&game);

        /* Отрисовка */
        game_render(&game);

        /* FPS */
        SDL_Delay(DELAY);
    }

    // Уничтожение текстуры
    SDL_DestroyTexture(game.textures.player_frames[0]);
    SDL_DestroyTexture(game.textures.player_frames[1]);
    SDL_DestroyTexture(game.textures.ledge);
    SDL_DestroyTexture(game.textures.star);

    // Закрытие и уничтожение окна
    SDL_DestroyWindow(window);
    // Закрытие и уничтожение визуализатора
    SDL_DestroyRenderer(game.rndr);

    // Выход из SDL2
    SDL_Quit();

    return 0;
}