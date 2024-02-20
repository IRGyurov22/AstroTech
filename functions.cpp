#include "functions.h"
#include "raylib.h"
#include <chrono>
#include <thread>

#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION            330
#else   
#define GLSL_VERSION            100
#endif

int windowsHeight = 850;
int windowsWidth = 800;

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

bool IsSound = 0;
bool IsShootingAllowed = 1;
bool useShader = 1;

Vector2 laserPosition = { 0, 0 }; 
float laserIntensity = 0.0f;
Vector3 laserColor = { 1.0f, 0.0f, 0.0f };

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
        DrawRectangle(laser.x+21, laser.y, 5, 20, BLANK);
    }
}

void updateLaserParticles(vector<LaserParticle>& particles) {
    for (auto& particle : particles) {
        if (particle.active) {
            particle.position.x += particle.velocity.x;
            particle.position.y += particle.velocity.y;
            particle.lifeSpan--;
            if (particle.lifeSpan <= 0 || particle.position.y <= 0) {
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
            IsShootingAllowed = 0;
            useShader = 0;
            int QuestionNumber = GetRandomValue(1, 1);

            if (QuestionNumber == 1)
            {
                DrawText("TEST", 200, 275, 15, WHITE);
                DrawRectangleRec(answear1, BLANK);
                DrawText("TEST", 160, 335, 15, WHITE);
                DrawRectangleRec(answear2, BLANK);
                DrawText("TEST", 160, 410, 15, WHITE);
                DrawRectangleRec(answear3, BLANK);
                DrawText("TEST", 160, 485, 15, WHITE);
                DrawRectangleRec(answear4, BLANK);
                DrawText("TEST", 160, 560, 15, WHITE);
                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear1))
                {
                    IsQuestionAnsweared = 1;
                }
                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear2))
                {
                    IsQuestionAnsweared = 1;
                    points++;
                }
                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear3))
                {
                    IsQuestionAnsweared = 1;
                }
                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear4))
                {
                    IsQuestionAnsweared = 1;
                }
            }
            if (IsQuestionAnsweared == 1)
            {
                asteroid.active = false;
                laser.active = false;

                for (int i = 0; i < 30; i++) {
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
                IsShootingAllowed = 1;
                useShader = 1;
                laser.y = 1000;
            }
            
        }

        if (asteroid.y >= windowsHeight) {
            asteroid.active = false;
            for (int i = 0; i < 30; i++) {
                Particle particle;
                particle.position = { static_cast<float>(asteroid.x), static_cast<float>(asteroid.y) };
                particle.velocity = { static_cast<float>(GetRandomValue(-5, 5)), static_cast<float>(GetRandomValue(-5, 5)) };
                particle.color = GRAY;
                particle.radius = GetRandomValue(1, 3);
                particle.active = true;
                particles.push_back(particle);
            }
        }
    }
}

void drawAsteroid(const Asteroid& asteroid, Texture2D texture) {
    if (asteroid.active) {
        DrawTexture(texture, asteroid.x, asteroid.y, WHITE);
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

void updateLaserPositionAndIntensity(const Laser& laser) {
    laserPosition.x = laser.x-25;
    laserPosition.y = laser.y;
    laserIntensity = 5.0f;
    if (laserPosition.y<=0)
    {
        laserPosition.y = 1000;
        laserPosition.x = 1000;
    }
}

void initgame()
{
    int sposx = 375;
    int sposy = 700;

    

    Laser laser = { 0, 0, false };

    vector<Asteroid> asteroids;
    vector<Particle> particles;
    vector<LaserParticle> laserParticles;
    InitAudioDevice();
    InitWindow(windowsWidth, windowsHeight, "AstoGame");
    SetTargetFPS(60);

    Texture2D ship = LoadTexture("resources/photos/ship.png");
    Texture2D asteroid = LoadTexture("resources/photos/asteroid.png");
    Texture2D background = LoadTexture("resources/photos/background.png");

    Sound bgm = LoadSound("Sound/SpaceExploration.wav");
    chrono::steady_clock::time_point lastSpawnTime = chrono::steady_clock::now();
    
    Shader lighting = LoadShader("resources/shaders/lighting.vs","resources/shaders/lighting.fs");
    float lightPos[] = { 0.0f, 0.0f }; 
    SetShaderValue(lighting, GetShaderLocation(lighting, "lightPos"), lightPos, SHADER_UNIFORM_VEC2);

    float lightColor[] = { 1.0f, 1.0f, 1.0f };
    SetShaderValue(lighting, GetShaderLocation(lighting, "lightColor"), lightColor, SHADER_UNIFORM_VEC3);

    float viewPos[] = { 0.0f, 0.0f }; 
    SetShaderValue(lighting, GetShaderLocation(lighting, "viewPos"), viewPos, SHADER_UNIFORM_VEC2);

    
    int ambientStrengthLocation = GetShaderLocation(lighting, "ambientStrength");
    float ambientStrength = 0.1f; 
    SetShaderValue(lighting, ambientStrengthLocation, &ambientStrength, SHADER_UNIFORM_FLOAT);


    while (!WindowShouldClose()) {
        auto start = chrono::steady_clock::now();
        BeginDrawing();
        if (useShader == 1)
        {
            BeginShaderMode(lighting);

            updateLaserPositionAndIntensity(laser);

            SetShaderValue(lighting, GetShaderLocation(lighting, "lightPos"), &laserPosition, SHADER_UNIFORM_VEC2);
            SetShaderValue(lighting, GetShaderLocation(lighting, "lightIntensity"), &laserIntensity, SHADER_UNIFORM_FLOAT);
            SetShaderValue(lighting, GetShaderLocation(lighting, "lightColor"), &laserColor, SHADER_UNIFORM_VEC3);

        }
        
        DrawTexture(background,0, 0,WHITE);
        DrawTexture(ship,sposx, sposy,WHITE);
        
        movement(sposx, sposy);
        if (IsSound == 0)
        {
            PlaySound(bgm);
            IsSound = 1;
        }
        if (IsKeyPressed(KEY_F) && IsShootingAllowed == 1) {
            laser.active = true;
            laser.x = sposx + 25;
            laser.y = sposy;

            for (int i = 0; i < 10; i++) {
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

        

        updateParticles(particles);
        drawParticles(particles);
        for (size_t i = 0; i < asteroids.size(); i++) {
            updateAsteroid(asteroids[i], laser, particles);
            drawAsteroid(asteroids[i], asteroid);
        }
        asteroids.erase(remove_if(asteroids.begin(), asteroids.end(), [](const Asteroid& a) { return !a.active; }), asteroids.end());

        EndShaderMode();
        EndDrawing();
        
        auto end = chrono::steady_clock::now();
        auto diff = end - start;
        if (diff < chrono::milliseconds(16)) {
            this_thread::sleep_for(chrono::milliseconds(16) - diff);
        }
    }

    CloseWindow();
}