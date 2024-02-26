#include "raylib.h"
#include "functions.h"
#include <chrono>
#include <thread>

using namespace std;

int main()
{
    int menuWidth = 800;
    int menuHeight = 800;
    InitWindow(menuWidth, menuHeight, "Menu");

    Rectangle start = { 300, 300, 200, 100 };
    Rectangle settings = { 300, 400, 200, 100 };
    Rectangle exit = { 300, 500, 200, 100 };   
    
    Texture2D background = LoadTexture("resources/photos/background.png");
    auto font = LoadFont("resources/fonts/Anta-Regular.ttf");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        DrawTexture(background, 0, 0, WHITE);
        DrawRectangleRec(start, BLANK);
        DrawRectangleRec(settings, BLANK);
        DrawRectangleRec(exit, BLANK);
        DrawTextEx(font, "Space Cadet", { 265, 100 }, 65, 1, WHITE);
        DrawTextEx(font, "by AstroTech", { 310, 170 }, 40, 1, WHITE);
        DrawTextEx(font, "START", { 355, 340 }, 35, 1, WHITE);
        DrawTextEx(font, "SETTINGS", { 335, 440 }, 35, 1, WHITE);
        DrawTextEx(font, "EXIT", { 370, 540 }, 35, 1, WHITE);
        if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), start))
        {
            CloseWindow();
            initgame();
        }

        if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), settings))
        {
            CloseWindow();
            
        }

        if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), exit))
        {
            CloseWindow();
        }

        EndDrawing();
    }
}