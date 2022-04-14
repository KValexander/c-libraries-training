// Подключение стандартных библиотек
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
// Подключение библиотеки raylib
#include <raylib.h>
// Подключение заголовков
#include <main.h>

/* Загрузка текстуры */
void load_texture(Texture2D *texture, char src[], int w, int h) {
    Image image = LoadImage(src); // загрузка изображения
    ImageResize(&image, w, h); // изменение размеров
    *texture = LoadTextureFromImage(image); // загрузка текстуры
    UnloadImage(image); // выгрузка изображения
}

/* Новая жизнь */
void init_reset(Game *game) {
    sprintf(game->labels[0].text, "x %d", game->player.lives);
    game->current_screen = SCREEN_LIVES;

    game->player.rect.x = 100;
    game->player.rect.y = 100;
    game->player.dx = 0;
    game->player.dy = 0;
    game->player.is_dead = 0;
    game->player.on_platform = 0;
} 

/* Инициализация */
void init(Game *game) {

    /* Инициализация окна */
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib");
    SetTargetFPS(FPS); // FPS
    
    /* Инициализация генератора псевдо случайных чисел */
    srand(time(0));

    /* Инициализация текстур */
    load_texture(&game->textures.fire, "assets/fire.png", 64, 64); // огонь
    load_texture(&game->textures.star, "assets/star.png", 64, 64); // звезда
    load_texture(&game->textures.player[0], "assets/one.png", 48, 48); // игрок
    load_texture(&game->textures.player[1], "assets/two.png", 48, 48); // игрок
    load_texture(&game->textures.platform, "assets/platform.png", 256, 64); // платформа

    /* Инициализация шрифта */
    game->font = LoadFont("assets/invasion2000.ttf");

    /* Инициализация надписей */
    /* Надпись на экране состояния жизни */ 
    sprintf(game->labels[0].text, "x %d", 3);
    game->labels[0].size = MeasureTextEx(game->font, game->labels[0].text, 36, 2);
    game->labels[0].pos.x = SCREEN_WIDTH / 2 - game->labels[0].size.x / 2 + 50;
    game->labels[0].pos.y = SCREEN_HEIGHT / 2 - game->labels[0].size.y / 2;

    /* Надпись на экране окончания игры */
    sprintf(game->labels[1].text, "Game over");
    game->labels[1].size = MeasureTextEx(game->font, game->labels[1].text, 48, 2);
    game->labels[1].pos.x = SCREEN_WIDTH / 2 - game->labels[1].size.x / 2;
    game->labels[1].pos.y = SCREEN_HEIGHT / 2 - game->labels[1].size.y / 2;

    /* Инициализация игрока */
    game->player.rect.w = 48;
    game->player.rect.h = 48;
    game->player.rect.x = 100;
    game->player.rect.y = 100;
    game->player.dx = 0;
    game->player.dy = 0;
    game->player.lives = 3;
    game->player.is_dead = 0;
    game->player.on_platform = 0;
    game->player.current_frame = 0;

    /* Инициализация камеры */
    game->camera.x = 0;
    game->camera.y = 0;

    /* Инициализация прочего */
    game->frame = 0; // время
    game->death_countdown = -1; // счётчик смерти

    /* Инициализация экранов */ 
    game->current_screen = SCREEN_LIVES;

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

    /* Рестарт */
    if(IsKeyDown(KEY_R))
        init_reset(game);

    /* Прыжок */
    if(IsKeyDown(KEY_UP)) {
        game->player.current_frame = 1;
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
        game->player.current_frame = 0;
        game->player.dx *= 0.8f;
        if(fabsf(game->player.dx) < 0.1f)
            game->player.dx = 0;
    }

}

/* Обновление данных экрана состояния жизни */
void update_lives(Game *game) {}

/* Обновление данных экрана игры */
void update_game(Game *game) {

    /* Если игрок жив */
    if(!game->player.is_dead) {

        /* Передвижение игрока */
        Player *player = &game->player;
        player->rect.x += player->dx;
        player->rect.y += player->dy;

        /* Анимация игрока */
        if(player->dx != 0 && player->on_platform)
            if(game->frame % 10 == 0)
                player->current_frame = !player->current_frame;

        player->dy += GRAVITY; // гравитация

    }

    /* Если игрок мёртв */
    if(game->player.is_dead && game->death_countdown < 0)
        game->death_countdown = 120;

    /* Обратный отсчёт смерти */ 
    if(game->death_countdown >= 0) {
        game->death_countdown--;
        if(game->death_countdown < 0) {

            /* Смерть игрока */
            game->player.lives--;
            game->frame = 0;

            /* Если у игрока остались жизни */ 
            if(game->player.lives >= 0)
                init_reset(game);

            /* Окончательная смерть */
            else game->current_screen = SCREEN_GAMEOVER;

        }
    }

}

/* Обновление данных экрана окончания игры */
void update_game_over(Game *game) {}

/* Обновление данных */
void update(Game *game) {
    game->frame++; // счётчик времени

    /* Время экрана загрузки */ 
    if(game->frame > 120 && game->current_screen != SCREEN_GAMEOVER)
        game->current_screen = SCREEN_GAME;

    /* Распределение экранов */ 
    switch(game->current_screen) {

        /* Экран состояния жизни */
        case SCREEN_LIVES:

            update_lives(game);

        break;

        /* Экран игры */
        case SCREEN_GAME:

            update_game(game);

        break;

        /* Экран окончаения игры */ 
        case SCREEN_GAMEOVER:

            update_game_over(game);

        break;

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

/* Отрисовка экрана состояния жизни */
void render_lives(Game *game) {

    /* Отрисовка игрока */
    DrawTexture(
        game->textures.player[0],
        SCREEN_WIDTH / 2 - game->player.rect.w /2 - 20,
        SCREEN_HEIGHT / 2 - game->player.rect.h / 2,
        WHITE // зачем?
    );

    /* Отрисовка текста */
    DrawTextEx(
        game->font,
        game->labels[0].text,
        game->labels[0].pos,
        36,
        2,
        WHITE
    );

}

/* Отрисовка экрана игры */
void render_game(Game *game) {
    ClearBackground(SKYBLUE); // задний фон

    /* Отрисовка игрока */
    DrawTexture(
        game->textures.player[game->player.current_frame],
        game->camera.x + game->player.rect.x,
        game->player.rect.y,
        WHITE // зачем?
    );

    /* Отрисовка огня в случае смерти игрока */
    if(game->player.is_dead)
        DrawTexture(
            game->textures.fire,
            game->camera.x+game->player.rect.x - 6,
            game->player.rect.y - 6,
            WHITE // зачем?
        );

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

}

/* Отрисовка экрана окончания игры */
void render_game_over(Game *game) {

    /* Отрисовка текста */
    DrawTextEx(
        game->font,
        game->labels[1].text,
        game->labels[1].pos,
        48,
        2,
        WHITE
    );

}

/* Отрисовка */
void render(Game *game) {
    ClearBackground(BLACK); // задний фон

    /* Распределение экранов */ 
    switch(game->current_screen) {

        /* Экран количества жизней */
        case SCREEN_LIVES:

            render_lives(game);

        break;

        /* Экран игры */
        case SCREEN_GAME:

            render_game(game);

        break;

        /* Экран проигрыша */ 
        case SCREEN_GAMEOVER:

            render_game_over(game);

        break;

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
    UnloadTexture(game->textures.fire);
    UnloadTexture(game->textures.star);
    UnloadTexture(game->textures.player[0]);
    UnloadTexture(game->textures.player[1]);
    UnloadTexture(game->textures.platform);

    /* Выгрузка шрифтов */
    UnloadFont(game->font);

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