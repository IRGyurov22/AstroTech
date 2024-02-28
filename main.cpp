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

    Rectangle start = { 300, 325, 200, 100 };
    Rectangle controls = { 300, 400, 200, 100 };
    Rectangle exit = { 300, 500, 200, 100 };   
    
    Texture2D background = LoadTexture("resources/photos/background.png");
    auto font = LoadFont("resources/fonts/Anta-Regular.ttf");

    bool startgame = 0;
    bool exitgame = 0;
    while (!WindowShouldClose())
    {
        BeginDrawing();
        DrawTexture(background, 0, 0, WHITE);
        DrawRectangleRec(start, BLANK);
        DrawRectangleRec(controls, BLANK);
        DrawRectangleRec(exit, BLANK);
        DrawTextEx(font, "Space Cadet", { 245, 100 }, 65, 1, WHITE);
        DrawTextEx(font, "by AstroTech", { 302, 170 }, 40, 1, WHITE);
        DrawTextEx(font, "START", { 320, 350 }, 55, 1, WHITE);
        DrawTextEx(font, "EXIT", { 343, 570 }, 55, 1, WHITE);
        if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), start))
        {
            startgame = 1;
            CloseWindow();
            break;
        }

        if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), exit))
        {
            exitgame = 0;
            break;
        }

        EndDrawing();
    }
    if (startgame)
    {
        initgame();
    }
    if (exitgame)
    {
        CloseWindow();
    }
}