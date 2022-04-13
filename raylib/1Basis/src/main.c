// Подключение стандартных библиотек
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
// Подключение библиотеки raylib
#include <raylib.h>
// Подключение заголовков
#include <main.h>

/* Инициализация */
void init(Game *game) {

    /* Инициализация окна */
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib");
    SetTargetFPS(FPS); // FPS
    
    /* Инициализация генератора псевдо случайных чисел */
    srand(time(0));

    /* Инициализация текстур */
    Image image;

    /* Огонь */
    image = LoadImage("assets/fire.png"); // загрузка изображения
    ImageResize(&image, 64, 64); // изменение размеров
    game->textures.fire = LoadTextureFromImage(image); // загрузка текстуры
    UnloadImage(image); // выгрузка изображения

    /* Звезда */
    image = LoadImage("assets/star.png"); // загрузка изображения
    ImageResize(&image, 64, 64); // изменение размеров
    game->textures.star = LoadTextureFromImage(image); // загрузка текстуры
    UnloadImage(image); // выгрузка изображения

    /* Игрок */
    image = LoadImage("assets/star.png"); // загрузка изображения
    ImageResize(&image, 48, 48); // изменение размеров
    game->textures.player = LoadTextureFromImage(image); // загрузка текстуры
    UnloadImage(image); // выгрузка изображения

    /* Платформа */ 
    image = LoadImage("assets/platform.png"); // загрузка изображения
    ImageResize(&image, 256, 64); // изменение размеров
    game->textures.platform = LoadTextureFromImage(image); // загрузка текстуры
    UnloadImage(image); // выгрузка изображения

    /* Инициализация игрока */
    game->player.rect.w = 48;
    game->player.rect.h = 48;
    game->player.rect.x = 100;
    game->player.rect.y = 100;
    game->player.dx = 0;
    game->player.dy = 0;
    game->player.is_dead = 0;
    game->player.on_platform = 0;

    /* Инициализация камеры */
    game->camera.x = 0;
    game->camera.y = 0;

    /* Инициализация прочего */
    game->frame = 0;
    game->current_screen = SCREEN_GAME;

    /* Инициализация звёзд */
    for (int i = 0; i < NUM_STARS; i++) {
        game->stars[i].w = 64;
        game->stars[i].h = 64;
        game->stars[i].x = SCREEN_WIDTH / 2 + rand() % 38400;
        game->stars[i].y = rand() % 480;
    }

    /* Инициализация платформ */
    for (int i = 0; i < NUM_PLATFORMS; i++) {
        game->platforms[i].w = 256;
        game->platforms[i].h = 64;
        game->platforms[i].x = i*384;
        game->platforms[i].y = 300 + 100 - rand() % 200;
    } game->platforms[0].y = 400;

}

/* Обработка событий */
void events(Game *game) {

    /* Прыжок */
    if(IsKeyDown(KEY_UP)) {
        if(game->player.on_platform) {
            game->player.dy = -8;
            game->player.on_platform = 0;
        } game->player.dy -= 0.2f;
    }

    /* Движение в право */ 
    if(IsKeyDown(KEY_RIGHT)) {
        game->player.dx += 0.5;
        if(game->player.dx > 6)
            game->player.dx = 6;
    }

    /* Движение в лево */ 
    else if(IsKeyDown(KEY_LEFT)) {
        game->player.dx -= 0.5;
        if(game->player.dx < -6)
            game->player.dx = -6;
    }

    /* Остановка движения */ 
    else {
        game->player.dx *= 0.8f;
        if(fabsf(game->player.dx) < 0.1f)
            game->player.dx = 0;
    }

}

/* Обновление данных */
void update(Game *game) {
    game->frame++; // счётчик времени

    /* Распределение экранов */ 
    switch(game->current_screen) {

        /* Экран количества жизней */
        case SCREEN_LIVES: break;

        /* Экран игры */
        case SCREEN_GAME:

            /* Если игрок жив */
            if(!game->player.is_dead) {

                /* Передвижение игрока */
                Player *player = &game->player;
                player->rect.x += player->dx;
                player->rect.y += player->dy;

                player->dy += GRAVITY; // гравитация

            }


        break;

        /* Экран проигрыша */ 
        case SCREEN_GAMEOVER: break;

        default: break;
    }

    /* Камера */
    game->camera.x = -game->player.rect.x + (SCREEN_WIDTH / 2 - game->player.rect.w / 2);
    if(game->camera.x > 0) game->camera.x = 0;
}

/* Проверка коллизии */
int collide_2d(float x1, float y1, float x2, float y2, float wt1, float ht1, float wt2, float ht2) {
    return (!((x1 > (x2+wt2)) || (x2 > (x1+wt1)) || (y1 > (y2+ht2)) || (y2 > (y1+ht1))));
}

/* Обработка коллизий */
void collisions(Game *game) {

    /* Проверка коллизий на столкновение со звёздами */
    for(int i = 0; i < NUM_STARS; i++)
        if(collide_2d(
            game->player.rect.x,
            game->player.rect.y,
            game->stars[i].x+game->stars[i].w/4,
            game->stars[i].y+game->stars[i].w/4,
            game->player.rect.w,
            game->player.rect.h,
            game->stars[i].w/2,
            game->stars[i].h/2)
        ) game->player.is_dead = 1;   

    /* Проверка коллизий на столкновение с платформами */
    for(int i = 0; i < NUM_PLATFORMS; i++) {

        /* Получение данных */
        float mx = game->player.rect.x, my = game->player.rect.y;
        float mw = game->player.rect.w, mh = game->player.rect.h;
        float bx = game->platforms[i].x, by = game->platforms[i].y;
        float bw = game->platforms[i].w, bh = game->platforms[i].h;

        /* Если задел 1 */
        if (mx + mw / 2 > bx && mx + mw / 2 < bx + bw) {
            if (my < by + bh && my > by && game->player.dy < 0) {
                game->player.rect.y = by + bh;
                my = by + bh;

                game->player.dy = 0;
                game->player.on_platform = 1;
            }
        }

        /* Если задел 2 */
        if (mx + mw > bx && mx < bx + bw) {
            if (my + mh > by && my < by && game->player.dy > 0) {
                game->player.rect.y = by - mh;
                my = by - mh;

                game->player.dy = 0;
                game->player.on_platform = 1;
            }
        }

        /* Если задел 3 */
        if (my + mh > by && my < by + bh) {
            /* Правая сторона */
            if (mx < bx + bw && mx + mw > bx + bw && game->player.dx < 0) {
                game->player.rect.x = bx + bw;
                mx = bx + bw;

                game->player.dx = 0;
            }
            /* Левая сторона */
            else if (mx + mw > bx && mx < bx && game->player.dx > 0) {
                game->player.rect.x = bx - mw;
                mx = bx - mw;

                game->player.dx = 0;
            }
        }
    }

}

/* Отрисовка */
void render(Game *game) {
    ClearBackground(SKYBLUE); // задний фон

    /* Распределение экранов */ 
    switch(game->current_screen) {

        /* Экран количества жизней */
        case SCREEN_LIVES: break;

        /* Экран игры */
        case SCREEN_GAME:

            /* Отрисовка игрока */
            DrawRectangle(
                game->camera.x+game->player.rect.x,
                game->player.rect.y,
                game->player.rect.w,
                game->player.rect.h,
                BLUE
            );

            /* Отрисовка огня в случае смерти игрока */
            if(game->player.is_dead) {
                Vector2 xy = {game->camera.x+game->player.rect.x - 6, game->player.rect.y - 6};
                DrawTextureEx(
                    game->textures.fire,
                    xy,
                    0,
                    1,
                    WHITE
                );
            }

            /* Отрисовка Звёзд */
            for(int i = 0; i < NUM_STARS; i++)
                DrawTexture(
                    game->textures.star,
                    game->camera.x + game->stars[i].x,
                    game->stars[i].y,
                    WHITE // зачем?
                );

            /* Отрисовка платформ */
            for(int i = 0; i < NUM_PLATFORMS; i++)
                DrawTexture(
                    game->textures.platform,
                    game->camera.x + game->platforms[i].x,
                    game->platforms[i].y,
                    WHITE // зачем?
                );

        break;

        /* Экран проигрыша */ 
        case SCREEN_GAMEOVER: break;

        default: break;
    }

}

/* Игровой цикл */
void loop(Game *game) {

    while(!WindowShouldClose()) {

        /* Обработка событий */
        events(game);

        /* Обновление данных */
        update(game);

        /* Обработка коллизий */
        collisions(game);

        /* Отрисовка */
        BeginDrawing(); // начало отрисовки

            render(game); // функция отрисовки

        EndDrawing(); // окончание отрисовки
    }

}

/* Деинициализация */
void deinit(Game *game) {

    /* Выгрузка текстур */
    UnloadTexture(game->textures.star);
    UnloadTexture(game->textures.player);
    UnloadTexture(game->textures.platform);

    /* Закрытие окна */
    CloseWindow();

}

/* Точка входа */ 
int main(void) {
    /* Объявление структуры Игрок */ 
    Game game;

    /* Инициализация */
    init(&game);

    /* Игровой цикл */
    loop(&game);

    /* Деинициализация */
    deinit(&game);


    return 0;
}