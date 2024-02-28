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

    Rectangle start = { 300, 405, 200, 50 };
    Rectangle exit = { 300, 500, 200, 50 };   
    
    Texture2D background = LoadTexture("resources/photos/background.png");
    auto font = LoadFont("resources/fonts/Anta-Regular.ttf");

    bool startgame = 0;
    bool exitgame = 0;
    while (!WindowShouldClose())
    {
        BeginDrawing();
        DrawTexture(background, 0, 0, WHITE);
        DrawRectangleRec(start, BLANK);
        DrawRectangleRec(exit, BLANK);
        DrawTextEx(font, "Space Cadet", { 190, 110 }, 85, 1, WHITE);
        DrawTextEx(font, "by AstroTech", { 260, 200 }, 55, 1, WHITE);
        DrawTextEx(font, "START", { 315, 400 }, 65, 1, WHITE);
        DrawTextEx(font, "EXIT", { 340, 490 }, 65, 1, WHITE);
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