#include "movement.h"
#include "raylib.h"

// Define the movement of the game.
 void movement(int& AstroPosX, int& AstroPosy,int& MovementSpeed) {
    if (IsKeyDown(KEY_RIGHT)) {
        if (AstroPosX + MovementSpeed > 800)
        {
            AstroPosX = 800;
        }
        else
        {
            AstroPosX += MovementSpeed;
        }
    }
    if (IsKeyDown(KEY_LEFT)) {
        if (AstroPosX - MovementSpeed < 0)
        {
            AstroPosX = 0;
        }
        else
        {
            AstroPosX -= MovementSpeed;
        }

    }
    if (IsKeyDown(KEY_UP)) {
        if (AstroPosy - MovementSpeed < 0)
        {
            AstroPosy = 0;
        }
        else
        {
            AstroPosy -= MovementSpeed;
        }

    }
    if (IsKeyDown(KEY_DOWN)) {
        if (AstroPosy + MovementSpeed > 800)
        {
            AstroPosy = 800;
        }
        else
        {
            AstroPosy += MovementSpeed;
        }

    }

}