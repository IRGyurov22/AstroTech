#include "functions.h"
#include "raylib.h"
#include <chrono>
#include <thread>


Rectangle answear1 = { 150, 325, 200, 50 };
Rectangle answear2 = { 150, 400, 200, 50 };
Rectangle answear3 = { 150, 475, 200, 50 };
Rectangle answear4 = { 150, 550, 200, 50 };

int laserspeed = 7;
int movementSpeed = 4;
int asteroidspeed = 2; 

bool IsQuestionAnsweared = 0;
int AsteroidSpawnTime = 4;

int points = 0;

void movement(int& sposx, int& sposy) {
    if (IsKeyDown(KEY_RIGHT)) {
        sposx += movementSpeed;
    }
    if (IsKeyDown(KEY_LEFT)) {
        sposx -= movementSpeed;
    }
    if (IsKeyDown(KEY_UP)) {
        sposy -= movementSpeed;
    }
    if (IsKeyDown(KEY_DOWN)) {
        sposy += movementSpeed;
    }
}

void updateLaser(Laser& laser) {
    if (laser.active) {
        laser.y -= laserspeed;

        if (laser.y <= 0) {
            laser.active = false;
        }
    }
}

void drawLaser(Laser& laser) {
    if (laser.active) {
        DrawRectangle(laser.x, laser.y, 5, 20, RED);
    }
}

void updateLaserParticles(vector<LaserParticle>& particles) {
    for (auto& particle : particles) {
        if (particle.active) {
            particle.position.x += particle.velocity.x;
            particle.position.y += particle.velocity.y;
            particle.lifeSpan--;
            if (particle.lifeSpan <= 0) {
                particle.active = false;
            }
        }
    }
}

void drawLaserParticles(const vector<LaserParticle>& particles) {
    for (const auto& particle : particles) {
        if (particle.active) {
            DrawCircle(particle.position.x, particle.position.y, particle.radius, particle.color);
        }
    }
}

void updateAsteroid(Asteroid& asteroid, Laser& laser, vector<Particle>& particles) {
    if (asteroid.active) {
        asteroid.y += asteroidspeed;

        if (CheckCollisionRecs({ (float)laser.x, (float)laser.y, 5, 20 }, { (float)asteroid.x - asteroid.size / 2, (float)asteroid.y - asteroid.size / 2, (float)asteroid.size, (float)asteroid.size })) {
            
            DrawRectangle(100, 250, 600, 400, GRAY);

            laserspeed = 0;
            movementSpeed = 0;
            asteroidspeed = 0;
            AsteroidSpawnTime = 999999;

            int QuestionNumber = GetRandomValue(1, 1);

            if (QuestionNumber == 1)
            {
                DrawText("TEST", 200, 275, 15, BLACK);
                DrawRectangleRec(answear1, WHITE);
                DrawText("TEST", 160, 335, 15, BLACK);
                DrawRectangleRec(answear2, WHITE);
                DrawText("TEST", 160, 410, 15, BLACK);
                DrawRectangleRec(answear3, WHITE);
                DrawText("TEST", 160, 485, 15, BLACK);
                DrawRectangleRec(answear4, WHITE);
                DrawText("TEST", 160, 560, 15, BLACK);
                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear1))
                {
                    IsQuestionAnsweared = 0;
                }
                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear2))
                {
                    IsQuestionAnsweared = 1;
                    points++;
                }
                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear3))
                {
                    IsQuestionAnsweared = 0;
                }
                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear4))
                {
                    IsQuestionAnsweared = 0;
                }
            }
            if (IsQuestionAnsweared == 1)
            {
                asteroid.active = false;
                laser.active = false;

                for (int i = 0; i < 30; ++i) {
                    Particle particle;
                    particle.position = { static_cast<float>(asteroid.x), static_cast<float>(asteroid.y) };
                    particle.velocity = { static_cast<float>(GetRandomValue(-5, 5)), static_cast<float>(GetRandomValue(-5, 5)) };
                    particle.color = GRAY;
                    particle.radius = GetRandomValue(1, 3);
                    particle.active = true;
                    particles.push_back(particle);
                }

                IsQuestionAnsweared = 0;
                laserspeed = 7;
                movementSpeed = 4;
                asteroidspeed = 2;
                AsteroidSpawnTime = 4;

            }
            
        }

        if (asteroid.y >= 800) {
            asteroid.active = false;
        }
    }
}

void drawAsteroid(const Asteroid& asteroid) {
    if (asteroid.active) {
        DrawCircle(asteroid.x, asteroid.y, asteroid.size / 2, GRAY);
    }
}

void updateParticles(vector<Particle>& particles) {
    for (auto& particle : particles) {
        if (particle.active) {
            particle.position.x += particle.velocity.x;
            particle.position.y += particle.velocity.y;
        }
    }
}

void drawParticles(const vector<Particle>& particles) {
    for (const auto& particle : particles) {
        if (particle.active) {
            DrawCircle(static_cast<int>(particle.position.x), static_cast<int>(particle.position.y), particle.radius, particle.color);
        }
    }
}

void initgame()
{
    int sposx = 375;
    int sposy = 400;

    int windowsHeight = 850;
    int windowsWidth = 800;

    Laser laser = { 0, 0, false };

    vector<Asteroid> asteroids;
    vector<Particle> particles;
    vector<LaserParticle> laserParticles;

    InitWindow(windowsWidth, windowsHeight, "AstoGame");
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
        if (chrono::duration_cast<chrono::seconds>(currentTime - lastSpawnTime).count() >= AsteroidSpawnTime) {
            Asteroid asteroid;
            asteroid.x = GetRandomValue(50, 750);
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
}