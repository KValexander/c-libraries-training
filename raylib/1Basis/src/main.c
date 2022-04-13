// Подключение библиотеки raylib
#include <raylib.h>

int main(void) {

    const int screen_width = 800;
    const int screen_height = 450;

    // Инициализация окна
    InitWindow(screen_width, screen_height, "Raylib");
    // Установка FPS
    SetTargetFPS(30);

    // Игровой цикл, до тех пор, пока окно не будет закрыто
    while(!WindowShouldClose()) {

        // ??????? (ладно)
        // Начало отрисовки
        BeginDrawing();
        
            ClearBackground(RAYWHITE);
        
            DrawText("So simple?", 190, 200, 20, LIGHTGRAY);
        
        // Окончание отрисовки
        EndDrawing();

    }

    // Закрытие окна
    CloseWindow();

    return 0;
}