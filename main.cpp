#include "raylib.h"
#include "functions.h"
#include <chrono>
#include <thread>
using namespace std;
int main() {
    int sposx = 375;
    int sposy = 400;
    Laser laser = { 0, 0, false };

    vector<Asteroid> asteroids;
    vector<Particle> particles;
    vector<LaserParticle> laserParticles;

    InitWindow(800, 800, "test");
    SetTargetFPS(60);

    chrono::steady_clock::time_point lastSpawnTime = chrono::steady_clock::now();

    while (!WindowShouldClose()) {
        auto start = chrono::steady_clock::now();
        BeginDrawing();
        ClearBackground(BLACK);

        DrawRectangle(sposx, sposy, 50, 50, YELLOW);
        movement(sposx, sposy);

        if (IsKeyPressed(KEY_F)) {
            laser.active = true;
            laser.x = sposx + 25;
            laser.y = sposy;

            for (int i = 0; i < 10; ++i) {
                LaserParticle particle;
                particle.position = { static_cast<float>(laser.x), static_cast<float>(laser.y) };
                particle.velocity = { static_cast<float>(GetRandomValue(-2, 2)), static_cast<float>(GetRandomValue(-2, 2)) };
                particle.color = RED;
                particle.radius = GetRandomValue(1, 3);
                particle.lifeSpan = GetRandomValue(10, 30);
                particle.active = true;
                laserParticles.push_back(particle);
            }
        }

        updateLaser(laser);
        drawLaser(laser);
        updateLaserParticles(laserParticles);
        drawLaserParticles(laserParticles);
        chrono::steady_clock::time_point currentTime = chrono::steady_clock::now();
        if (chrono::duration_cast<chrono::seconds>(currentTime - lastSpawnTime).count() >= 4) {
            Asteroid asteroid;
            asteroid.x = GetRandomValue(20, 780);
            asteroid.y = -20;
            asteroid.size = GetRandomValue(30, 200);
            asteroid.active = true;
            asteroids.push_back(asteroid);
            lastSpawnTime = currentTime;
        }

        for (size_t i = 0; i < asteroids.size(); ++i) {
            updateAsteroid(asteroids[i], laser, particles);
            drawAsteroid(asteroids[i]);
        }

        updateParticles(particles);
        drawParticles(particles);

        asteroids.erase(remove_if(asteroids.begin(), asteroids.end(), [](const Asteroid& a) { return !a.active; }), asteroids.end());

        EndDrawing();

        auto end = chrono::steady_clock::now();
        auto diff = end - start;
        if (diff < chrono::milliseconds(16)) {
            this_thread::sleep_for(chrono::milliseconds(16) - diff);
        }
    }

    CloseWindow();
    return 0;
}
