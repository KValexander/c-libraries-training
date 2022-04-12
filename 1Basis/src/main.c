// Стандартные библиотеки
#include <stdio.h>
#include <time.h>
#include <math.h>
// Заголовки
#include "main.h"
#include "status.h"

// Константы
#define GRAVITY 0.35f

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

    // Загрузка шрифта
    game->font = TTF_OpenFont("assets/invasion2000.ttf", 36);
    if(!game->font) printf("Font not found");
    game->label_w = 0;
    game->label_h = 0;

    // Инициализация надписи
    game->textures.label = NULL;

    // Инициализация игрока
    game->player.x = 320-24;
    game->player.y = 240-24;
    game->player.w = 48;
    game->player.h = 48;
    game->player.dx = 0;
    game->player.dy = 0;
    game->player.lives = 3;
    game->player.on_ledge = 0;
    game->player.anim_frame = 0;
    game->player.facing_left = 0;

    // Инициализация состояния
    init_status_lives(game);

    game->time = 0;
    game->status = STATUS_LIVES;

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

    game->ledges[98].x = 350;
    game->ledges[98].y = 350;
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
                            game->player.dy = -8;
                            game->player.on_ledge = 0;
                        }
                    break;
                }
            break;

        }
    }

    // Обработка нажатий на клавиши
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    
    // Больше прыжков
    if(state[SDL_SCANCODE_UP])
        game->player.dy -= 0.2f;
    
    // Движение влево
    if(state[SDL_SCANCODE_LEFT]) {
        game->player.dx -= 0.5;
        if(game->player.dx < -6)
            game->player.dx = -6;
        game->player.facing_left = 1;
        game->player.slowing_down = 0;
    }
    // Движение вправо
    else if(state[SDL_SCANCODE_RIGHT]) {
        game->player.dx += 0.5;
        if(game->player.dx > 6)
            game->player.dx = 6;
        game->player.facing_left = 0;
        game->player.slowing_down = 0;
    }
    else {
        game->player.anim_frame = 0;
        game->player.dx *= 0.8f;
        game->player.slowing_down = 1;
        if(fabsf(game->player.dx) < 0.1f)
            game->player.dx = 0;
    }
    // // Движение вверх
    // if(state[SDL_SCANCODE_UP])
    //     game->player.y -= 10;
    // // Движение вниз
    // else if(state[SDL_SCANCODE_DOWN])
    //     game->player.y += 10;

    return quit;
}

// Обновление данных
void game_update(GameState *game) {
    // Добавление времени
    game->time++;

    // Состояние экрана загрузки
    if(game->time > 120) {
        shutdown_status_lives(game);
        // Переключение в состояние игры
        game->status = STATUS_GAME;
    }

    // Состояние игры
    if(game->status != STATUS_LIVES) {
        // Передвижение игрока
        Player *player = &game->player;
        player->x += player->dx;
        player->y += player->dy;

        if(player->dx != 0 && player->on_ledge && !player->slowing_down) {
            if(game->time % 10 == 0) {
                if(player->anim_frame == 0)
                    player->anim_frame = 1;
                else player->anim_frame = 0;
            }
        }

        // Гравитация
        player->dy += GRAVITY;
    }
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
        // Если задел 1
        if (mx + mw / 2 > bx && mx + mw / 2 < bx + bw) {
            if (my < by + bh && my > by && game->player.dy < 0) {
                game->player.y = by + bh;
                my = by + bh;

                game->player.dy = 0;
                game->player.on_ledge = 1;
            }
        }

        // Если задел 2
        if (mx + mw > bx && mx < bx + bw) {
            if (my + mh > by && my < by && game->player.dy > 0) {
                game->player.y = by - mh;
                my = by - mh;

                game->player.dy = 0;
                game->player.on_ledge = 1;
            }
        }

        // Если задел 3
        if (my + mh > by && my < by + bh) {
            // Правая сторона
            if (mx < bx + bw && mx + mw > bx + bw && game->player.dx < 0) {
                game->player.x = bx + bw;
                mx = bx + bw;

                game->player.dx = 0;
            }
            // Левая сторона
            else if (mx + mw > bx && mx < bx && game->player.dx > 0) {
                game->player.x = bx - mw;
                mx = bx - mw;

                game->player.dx = 0;
            }
        }

        // Если задел 2
        // if (mx + mw > bx && mx < bx + bw) {
        //     // Верхняя сторона
        //     if (my < by + bh && my > by) {
        //         game->player.y = by + bh;
        //         game->player.dy = 0;
        //         game->player.on_ledge = 1;
        //     }
        //     // Нижняя сторона
        //     else if (my + mh > by && my < by) {
        //         game->player.y = by - mh;
        //         game->player.dy = 0;
        //         game->player.on_ledge = 1;
        //     }
        // }
    }
}


// Отрисовка
void game_render(GameState *game) {

    // Загрузочный экран
    if(game->status == STATUS_LIVES)
        draw_status_lives(game);
    
    // Экран игры
    else if(game->status == STATUS_GAME) {
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
        SDL_RenderCopyEx(
            game->rndr,
            game->textures.player_frames[game->player.anim_frame],
            NULL,
            &player_rect,
            0,
            NULL,
            game->player.facing_left
        ); // отрисовка текстуры

        // Создание и отрисовка звёзд
        // for(int i = 0; i < 100; i++) {
        //     SDL_Rect star_rect = {game->stars[i].x, game->stars[i].y, 32, 32};  // создание прямоугольника
        //     SDL_RenderCopy(game->rndr, game->textures.star, NULL, &star_rect); // отрисовка текстуры
        // }
    }


    // Отрисовка объектов на окне
    SDL_RenderPresent(game->rndr);
}

// Старт
int main(int argc, char *argv[]) {

    // Объявление констант
    const int FPS = 60;
    const int DELAY = 1000 / FPS;

    // Объявление переменных
    int quit = 0; // игровой цикл

    SDL_Window *window = NULL; // Объявление окна
    GameState game; // Структура Состояние игры

    // Инициализация 
    SDL_Init(SDL_INIT_VIDEO); // SDL2
    TTF_Init(); // SDL2_ttf
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

        /* Обновление данных */
        game_update(&game);

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
    if (game.textures.label != NULL)
        SDL_DestroyTexture(game.textures.label);
    // Закрытие шрифта
    TTF_CloseFont(game.font);

    // Закрытие и уничтожение окна
    SDL_DestroyWindow(window);
    // Закрытие и уничтожение визуализатора
    SDL_DestroyRenderer(game.rndr);

    // Выход из SDL2_ttf
    TTF_Quit();
    // Выход из SDL2
    SDL_Quit();

    return 0;
}