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


    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawRectangleRec(start, WHITE);
        DrawRectangleRec(settings, WHITE);
        DrawRectangleRec(exit, WHITE);
        DrawText("START", 355, 340, 25, BLACK);
        DrawText("SETTINGS", 335, 440, 25, BLACK);
        DrawText("EXIT", 370, 540, 25, BLACK);

        if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), start))
        {
            CloseWindow();
            initgame();
        }

        if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), exit))
        {
            CloseWindow();
        }

        EndDrawing();
    }

}