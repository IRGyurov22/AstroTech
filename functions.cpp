#include "functions.h"
#include "raylib.h"
#include "Draws.h"

#include <chrono>
#include <thread>
#include <string>

#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION            330
#else   
#define GLSL_VERSION            100
#endif


Font font;

int windowsHeight = 850;
int windowsWidth = 800;

bool IsFontLoaded = 0;
bool IsFontLoadedQuestion = 0;
bool IsShaderLoaded = 0;
bool ShouldFightBoss = 0;

Rectangle answear1 = { 130, 415, 240, 50 };
Rectangle answear2 = { 440, 415, 240, 50 };
Rectangle answear3 = { 130, 525, 240, 50 };
Rectangle answear4 = { 440, 525, 240, 50 };

int movementSpeed = 4;
int asteroidspeed = 2;

bool IsQuestionAnsweared = 0;
int AsteroidSpawnTime = 4;

int points = 0;

bool IsSound = 0;
bool IsShootingAllowed = 1;
bool useShader = 1;
bool IsGameStarted = 0;

int QuestionNumber = GetRandomValue(1, 10);


int laserspeed = 7;
Vector2 laserPosition = { 0, 0 };
float laserIntensity = 0.0f;
Vector3 laserColor = { 1.0f, 0.0f, 0.0f };

void movement(int& AstroPosX, int& AstroPosy) {
    if (IsKeyDown(KEY_RIGHT)) {
        if (AstroPosX + movementSpeed > 800)
        {
            AstroPosX = 800;
        }
        else
        {
            AstroPosX += movementSpeed;
        }
    }
    if (IsKeyDown(KEY_LEFT)) {
        if (AstroPosX - movementSpeed < 0)
        {
            AstroPosX = 0;
        }
        else
        {
            AstroPosX -= movementSpeed;
        }

    }
    if (IsKeyDown(KEY_UP)) {
        if (AstroPosy - movementSpeed < 0)
        {
            AstroPosy = 0;
        }
        else
        {
            AstroPosy -= movementSpeed;
        }

    }
    if (IsKeyDown(KEY_DOWN)) {
        if (AstroPosy +  movementSpeed > 800)
        {
            AstroPosy = 800;
        }
        else
        {
            AstroPosy += movementSpeed;
        }

    }

}
void updateAsteroid(Asteroid& asteroid, Laser& laser, vector<Particle>& particles, Texture2D TextWindow) {


    if (asteroid.active) {
        asteroid.y += asteroidspeed;

        if (CheckCollisionRecs({ (float)laser.x, (float)laser.y, 5, 20 }, { (float)asteroid.x - asteroid.size / 2, (float)asteroid.y - asteroid.size / 2, (float)asteroid.size, (float)asteroid.size })) {
            if (IsFontLoadedQuestion == 0)
            {
                font = LoadFont("resources/fonts/Anta-Regular.ttf");
                IsFontLoadedQuestion = 1;
            }
            DrawTexture(TextWindow, 105, 210, GRAY);
            useShader = 0;
            laserspeed = 0;
            movementSpeed = 0;
            asteroidspeed = 0;
            AsteroidSpawnTime = 999999;
            IsShootingAllowed = 0;
            switch (QuestionNumber)
            {
            case 1:
                DrawTextEx(font, " A projectile fired with initial velocity u at some angle 0 has \n a range R. If the initial velocity be keeping the angle of \n projection same, then the range will be", { 110, 230 }, 24, 1, WHITE);
                DrawRectangleRec(answear1, BLANK);
                DrawTextEx(font, "1. R/2", { 140, 425 }, 30, 1, WHITE);
                DrawRectangleRec(answear2, BLANK);
                DrawTextEx(font, "2. 4R", { 450, 425 }, 30, 1, WHITE);
                DrawRectangleRec(answear3, BLANK);
                DrawTextEx(font, "3. 2R", { 140, 535}, 30, 1, WHITE);
                DrawRectangleRec(answear4, BLANK);
                DrawTextEx(font, "4. None of the above", { 450, 535 }, 28, 1, WHITE);

                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear2))
                {
                    IsQuestionAnsweared = 1;
                    points++;
                }
                else if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && (CheckCollisionPointRec(GetMousePosition(), answear1) || CheckCollisionPointRec(GetMousePosition(), answear3) || CheckCollisionPointRec(GetMousePosition(), answear4)))
                {
                    IsQuestionAnsweared = 1;
                    points--;
                }

                break;
            case 2:
                DrawTextEx(font, "What type of waves are light wave?", { 125, 280 }, 40, 1, WHITE);
                DrawRectangleRec(answear1, BLANK);
                DrawTextEx(font, "1. Transverse wave", { 140, 425 }, 28, 1, WHITE);
                DrawRectangleRec(answear2, BLANK);
                DrawTextEx(font, "2. Longitudinal wave", { 450, 425 }, 28, 1, WHITE);
                DrawRectangleRec(answear3, BLANK);
                DrawTextEx(font, "3. Both A & B", { 140, 535 }, 28, 1, WHITE);
                DrawRectangleRec(answear4, BLANK);
                DrawTextEx(font, "4. None", { 450, 535 }, 28, 1, WHITE);

                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear1))
                {
                    IsQuestionAnsweared = 1;
                    points++;
                }
                else if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && (CheckCollisionPointRec(GetMousePosition(), answear3) || CheckCollisionPointRec(GetMousePosition(), answear2) || CheckCollisionPointRec(GetMousePosition(), answear4)))
                {
                    IsQuestionAnsweared = 1;
                    points--;
                }
                break;
            case 3:
                DrawTextEx(font, " A 220 V, 100 W bulb is connected to a 110 V source. \n Calculate the power consumed by the bulb.", { 110, 250 }, 27, 1, WHITE);
                DrawRectangleRec(answear1, BLANK);
                DrawTextEx(font, "1. 10W", { 140, 425 }, 28, 1, WHITE);
                DrawRectangleRec(answear2, BLANK);
                DrawTextEx(font, "2. 15W", { 450, 425 }, 28, 1, WHITE);
                DrawRectangleRec(answear3, BLANK);
                DrawTextEx(font, "3. 20W", { 140, 535 }, 28, 1, WHITE);
                DrawRectangleRec(answear4, BLANK);
                DrawTextEx(font, "4. 25W", { 450, 535 }, 28, 1, WHITE);

                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear4))
                {
                    IsQuestionAnsweared = 1;
                    points++;
                }
                else if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && (CheckCollisionPointRec(GetMousePosition(), answear3) || CheckCollisionPointRec(GetMousePosition(), answear2) || CheckCollisionPointRec(GetMousePosition(), answear1)))
                {
                    IsQuestionAnsweared = 1;
                    points--;
                }
                break;
            case 4:
                DrawTextEx(font, " The instrument _________ is used for detecting \n electric current is", { 110, 230 }, 26, 1, WHITE);
                DrawRectangleRec(answear1, BLANK);
                DrawTextEx(font, "1. Galvanometer", { 140, 425 }, 24, 1, WHITE);
                DrawRectangleRec(answear2, BLANK);
                DrawTextEx(font, "2. Tube tester", { 450, 425 }, 24, 1, WHITE);
                DrawRectangleRec(answear3, BLANK);
                DrawTextEx(font, "3. Altimeter", { 140, 535 }, 24, 1, WHITE);
                DrawRectangleRec(answear4, BLANK);
                DrawTextEx(font, "4. Fathometer", { 450, 535 }, 24, 1, WHITE);

                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear1))
                {
                    IsQuestionAnsweared = 1;
                    points++;
                }
                else if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && (CheckCollisionPointRec(GetMousePosition(), answear3) || CheckCollisionPointRec(GetMousePosition(), answear2) || CheckCollisionPointRec(GetMousePosition(), answear4)))
                {
                    IsQuestionAnsweared = 1;
                    points--;
                }
                break;

            case 5:
                DrawTextEx(font, " How much work is done in moving a charge of 5 C across \n two  points having a potential difference of 16 V?", { 110, 230 }, 25, 1, WHITE);
                DrawRectangleRec(answear1, BLANK);
                DrawTextEx(font, "1. 65 J", { 140, 425 }, 28, 1, WHITE);
                DrawRectangleRec(answear2, BLANK);
                DrawTextEx(font, "2. 45 J", { 450, 425 }, 28, 1, WHITE);
                DrawRectangleRec(answear3, BLANK);
                DrawTextEx(font, "3. 40 J", { 140, 535 }, 28, 1, WHITE);
                DrawRectangleRec(answear4, BLANK);
                DrawTextEx(font, "4. 80 J", { 450, 535 }, 28, 1, WHITE);

                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear4))
                {
                    IsQuestionAnsweared = 1;
                    points++;
                }
                else if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && (CheckCollisionPointRec(GetMousePosition(), answear3) || CheckCollisionPointRec(GetMousePosition(), answear2) || CheckCollisionPointRec(GetMousePosition(), answear1)))
                {
                    IsQuestionAnsweared = 1;
                    points--;
                }
                break;
            case 6:
                DrawTextEx(font, "'Decibel' is the unit used for measuring :", { 110, 280 }, 37, 1, WHITE);
                DrawRectangleRec(answear1, BLANK);
                DrawTextEx(font, "1. Speed of light", { 140, 425 }, 25, 1, WHITE);
                DrawRectangleRec(answear2, BLANK);
                DrawTextEx(font, "2. Itensity of sound", { 450, 425 }, 25, 1, WHITE);
                DrawRectangleRec(answear3, BLANK);
                DrawTextEx(font, "3. Itensity of heat", { 140, 535 }, 25, 1, WHITE);
                DrawRectangleRec(answear4, BLANK);
                DrawTextEx(font, "4. Itensity of earthquake", { 450, 535 }, 23, 1, WHITE);

                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear2))
                {
                    IsQuestionAnsweared = 1;
                    points++;
                }
                else if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && (CheckCollisionPointRec(GetMousePosition(), answear1) || CheckCollisionPointRec(GetMousePosition(), answear3) || CheckCollisionPointRec(GetMousePosition(), answear4)))
                {
                    IsQuestionAnsweared = 1;
                    points--;
                }
                break;
            case 7:
                DrawTextEx(font, "Rod and cone are found in:", { 140, 280 }, 49, 1, WHITE);
                DrawRectangleRec(answear1, BLANK);
                DrawTextEx(font, "1. Heart", { 140, 425 }, 27, 1, WHITE);
                DrawRectangleRec(answear2, BLANK);
                DrawTextEx(font, "2 Eyes", { 450, 425 }, 27, 1, WHITE);
                DrawRectangleRec(answear3, BLANK);
                DrawTextEx(font, "3. Lungs", { 140, 535 }, 27, 1, WHITE);
                DrawRectangleRec(answear4, BLANK);
                DrawTextEx(font, "4. None of the above", { 450, 535 }, 27, 1, WHITE);

                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear3))
                {
                    IsQuestionAnsweared = 1;
                    points++;
                }
                else if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && (CheckCollisionPointRec(GetMousePosition(), answear1) || CheckCollisionPointRec(GetMousePosition(), answear2) || CheckCollisionPointRec(GetMousePosition(), answear4)))
                {
                    IsQuestionAnsweared = 1;
                    points--;
                }
                break;
            case 8:
                DrawTextEx(font, " A passenger in a moving bus is thrown forward when \n the bus suddenly stops. This is explained", { 110, 265 }, 27, 1, WHITE);
                DrawRectangleRec(answear1, BLANK);
                DrawTextEx(font, "1. by Newton's first law", { 140, 425 }, 20, 1, WHITE);
                DrawRectangleRec(answear2, BLANK);
                DrawTextEx(font, "2. by Newton's second law", { 450, 425 }, 20, 1, WHITE);
                DrawRectangleRec(answear3, BLANK);
                DrawTextEx(font, "3. by Newton's third law", { 140, 535 }, 20, 1, WHITE);
                DrawRectangleRec(answear4, BLANK);
                DrawTextEx(font, "4. by the principle of \n conservation of momentum", { 450, 525 }, 17, 1, WHITE);

                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear1))
                {
                    IsQuestionAnsweared = 1;
                    points++;
                }
                else if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && (CheckCollisionPointRec(GetMousePosition(), answear3) || CheckCollisionPointRec(GetMousePosition(), answear2) || CheckCollisionPointRec(GetMousePosition(), answear4)))
                {
                    IsQuestionAnsweared = 1;
                    points--;
                }
                break;
            case 9:
                DrawTextEx(font, "At which point of the Earth is there no gravity?", { 120, 265 }, 30, 1, WHITE);
                DrawRectangleRec(answear1, BLANK);
                DrawTextEx(font, "1. At North and South Pole", { 140, 425 }, 21, 1, WHITE);
                DrawRectangleRec(answear2, BLANK);
                DrawTextEx(font, "2. At equator", { 450, 425 }, 24, 1, WHITE);
                DrawRectangleRec(answear3, BLANK);
                DrawTextEx(font, "3. On the ocean surface", { 140, 535 }, 22, 1, WHITE);
                DrawRectangleRec(answear4, BLANK);
                DrawTextEx(font, "4. At centre of the Earth", { 450, 535 }, 22, 1, WHITE);

                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear4))
                {
                    IsQuestionAnsweared = 1;
                    points++;
                }
                else if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && (CheckCollisionPointRec(GetMousePosition(), answear3) || CheckCollisionPointRec(GetMousePosition(), answear2) || CheckCollisionPointRec(GetMousePosition(), answear1)))
                {
                    IsQuestionAnsweared = 1;
                    points--;
                }
                break;
            case 10:
                DrawTextEx(font, "Which of the following space agencies \n uses a spacecraft named Hayabusa ?", { 110, 250 }, 38, 1, WHITE);
                DrawRectangleRec(answear1, BLANK);
                DrawTextEx(font, "1. National Aeronautics and \n Space Administration(NASA)", { 140, 415 }, 17, 1, WHITE);
                DrawRectangleRec(answear2, BLANK);
                DrawTextEx(font, "2. Centre national \n detudes spatiales (CNES)", { 450, 415 }, 18, 1, WHITE);
                DrawRectangleRec(answear3, BLANK);
                DrawTextEx(font, "3. China National \n Space Administration (CNSA)", { 140, 525 }, 18, 1, WHITE);
                DrawRectangleRec(answear4, BLANK);
                DrawTextEx(font, "4. Japan Aerospace \n Exploration Agency (JAXA)", { 450, 525 }, 18, 1, WHITE);

                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear4))
                {
                    IsQuestionAnsweared = 1;
                    points++;
                }
                else if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && (CheckCollisionPointRec(GetMousePosition(), answear3) || CheckCollisionPointRec(GetMousePosition(), answear2) || CheckCollisionPointRec(GetMousePosition(), answear1)))
                {
                    IsQuestionAnsweared = 1;
                    points++;
                }
                break;
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
                QuestionNumber = GetRandomValue(10, 10);
                IsQuestionAnsweared = 0;
                laserspeed = 7;
                movementSpeed = 4;
                asteroidspeed = 2;
                AsteroidSpawnTime = 4;
                IsShootingAllowed = 1;
                useShader = 1;
                laser.y = 1000;
                IsFontLoadedQuestion = 0;
            }

        }

        if (asteroid.y >= windowsHeight) {
            asteroid.active = false;
            for (int i = 0; i < 30; i++) {
                Particle particle;
                particle.position = { static_cast<float>(asteroid.x), static_cast<float>(asteroid.y) };
                particle.velocity = { static_cast<float>(GetRandomValue(-5, 5)), static_cast<float>(GetRandomValue(-5, 5)) };
                particle.color = GRAY;
                particle.radius = GetRandomValue(1, 12);
                particle.active = true;
                particles.push_back(particle);
            }
        }
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

void updateLaserParticles(std::vector<LaserParticle>& particles) {
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

void updateParticles(std::vector<Particle>& particles) {
    for (auto& particle : particles) {
        if (particle.active) {
            particle.position.x += particle.velocity.x;
            particle.position.y += particle.velocity.y;
        }
    }
}

void updateLaserPositionAndIntensity(const Laser& laser) {
    laserPosition.x = laser.x - 25;
    laserPosition.y = laser.y;
    laserIntensity = 5.0;
    if (laserPosition.y <= 0) {
        laserPosition.y = 1000;
        laserPosition.x = 1000;
    }
}

void updateBossLaser(BossLaser& bossLaser) {
    if (bossLaser.active) {
        bossLaser.y += laserspeed;
        if (bossLaser.y >= 800) {
            bossLaser.active = false;
        }
    }
}

void updateBossLaserParticles(std::vector<BossLaserParticle>& particles) {
    for (auto& particle : particles) {
        if (particle.active) {
            particle.position.x += particle.velocity.x;
            particle.position.y += particle.velocity.y;
            particle.lifeSpan--;
            if (particle.lifeSpan <= 0 || particle.position.y >= 800) {
                particle.active = false;
            }
        }
    }
}


float smooth(float a, float b, float t) {
    return a + t * (b - a);
}

void bossShoot(std::vector<LaserParticle>& laserParticles, int bossx) {
    for (int i = 0; i < 10; i++) {
        
        LaserParticle particle;
        particle.position = { static_cast<float>(bossx), static_cast<float>(50) };
        particle.velocity = { static_cast<float>(GetRandomValue(-2, 2)), static_cast<float>(GetRandomValue(-2, 2)) };
        particle.color = BLUE; 
        particle.radius = GetRandomValue(1, 3);
        particle.lifeSpan = GetRandomValue(10, 30);
        particle.active = true;
        laserParticles.push_back(particle);
    }
}
void bossmovement(int &bossx)
{
    int direction = GetRandomValue(1, 2);
    float target = bossx;
    if (direction == 1) {
        target -= 5;
        if (target <= 0) {
            target = 0; 
        }
    }
    else {
        target += 5;
        if (target >= 800) {
            target = 800;
        }
    }

    bossx = smooth(bossx, target, 0.1);
}

void initgame()
{
    int AstroPosX = 375;
    int AstroPosy = 700;

    BossLaser bossLaser = { 0, 0, false };
    Laser laser = { 0, 0, false };
    int bossx = 200;

    vector<Asteroid> asteroids;
    vector<Particle> particles;
    vector<LaserParticle> laserParticles;
    std::vector<BossLaserParticle> bossLaserParticles;

    InitAudioDevice();
    InitWindow(windowsWidth, windowsHeight, "AstoGame");
    SetTargetFPS(60);

    Texture2D TextWindow = LoadTexture("resources/photos/QuestionTextBox.png");
    Texture2D ship = LoadTexture("resources/photos/ship.png");
    Texture2D boss = LoadTexture("resources/photos/boss.png");
    Texture2D asteroid = LoadTexture("resources/photos/asteroid.png");
    Texture2D background = LoadTexture("resources/photos/background.png");

    Sound bgm = LoadSound("Sound/SpaceExploration.wav");
    chrono::steady_clock::time_point lastSpawnTime = chrono::steady_clock::now();
    Shader lighting = LoadShader("resources/shaders/lighting.vs", "resources/shaders/lighting.fs");

    float lightPos[] = { 0.0, 0.0 };
    SetShaderValue(lighting, GetShaderLocation(lighting, "lightPos"), lightPos, SHADER_UNIFORM_VEC2);

    float lightColor[] = { 1.0, 1.0, 1.0 };
    SetShaderValue(lighting, GetShaderLocation(lighting, "lightColor"), lightColor, SHADER_UNIFORM_VEC3);

    float viewPos[] = { 0.0, 0.0 };
    SetShaderValue(lighting, GetShaderLocation(lighting, "viewPos"), viewPos, SHADER_UNIFORM_VEC2);


    int ambientStrengthLocation = GetShaderLocation(lighting, "ambientStrength");
    float ambientStrength = 0.3;
    SetShaderValue(lighting, ambientStrengthLocation, &ambientStrength, SHADER_UNIFORM_FLOAT);
  
    float bossShootTimer = 0.0;
    constexpr float BossShootCooldown = 5.0;


    while (!WindowShouldClose()) {
        auto start = chrono::steady_clock::now();
        BeginDrawing();
        if (IsFontLoaded == 0)
        {
            font = LoadFont("resources/fonts/Anta-Regular.ttf");
            IsFontLoaded = 1;
        }
        if (useShader == 1 || IsShaderLoaded == 0)
        {
            BeginShaderMode(lighting);

            updateLaserPositionAndIntensity(laser);

            SetShaderValue(lighting, GetShaderLocation(lighting, "lightPos"), &laserPosition, SHADER_UNIFORM_VEC2);
            SetShaderValue(lighting, GetShaderLocation(lighting, "lightIntensity"), &laserIntensity, SHADER_UNIFORM_FLOAT);
            SetShaderValue(lighting, GetShaderLocation(lighting, "lightColor"), &laserColor, SHADER_UNIFORM_VEC3);
            IsShaderLoaded = 1;
        }
        DrawTexture(background, 0, 0, WHITE);
        DrawTexture(ship, AstroPosX, AstroPosy, WHITE);

        if (ShouldFightBoss == 1)
        {

                DrawTexture(boss, bossx, 50, BLUE);
                ambientStrength = 0.1;
                SetShaderValue(lighting, ambientStrengthLocation, &ambientStrength, SHADER_UNIFORM_FLOAT);
            movement(AstroPosX, AstroPosy);
            if (IsKeyPressed(KEY_SPACE) && IsShootingAllowed == 1) {
                laser.active = true;
                laser.x = AstroPosX + 25;
                laser.y = AstroPosy;

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
            
            if (IsShootingAllowed == 1) {
                bossShootTimer += GetFrameTime();
                if (bossShootTimer >= BossShootCooldown) {
                    
                    bossLaser.active = true;
                    bossLaser.x = bossx + 25;
                    bossLaser.y = 50;
                    for (int i = 0; i < 10; i++) {
                        BossLaserParticle particle;
                        particle.position = { static_cast<float>(bossLaser.x), static_cast<float>(bossLaser.y) };
                        particle.velocity = { static_cast<float>(GetRandomValue(-2, 2)), static_cast<float>(GetRandomValue(-2, 2)) };
                        particle.color = BLACK;
                        particle.radius = GetRandomValue(1, 3);
                        particle.lifeSpan = GetRandomValue(10, 30);
                        particle.active = true;
                        bossLaserParticles.push_back(particle);
                    }
                    bossShootTimer = 0.0;
                }
            }
            updateBossLaser(bossLaser);
            updateBossLaserParticles(bossLaserParticles);
            
            drawBossLaserParticles(bossLaserParticles);
            drawBossLaser(bossLaser);
            bossmovement(bossx);
            updateLaser(laser);
        }
        else {
            if (IsGameStarted == 0)
            {
                useShader = 0;
                DrawRectangle(100, 400, 600, 200, BLANK);
                DrawTextEx(font, " Hello Astro,\n Y..o??u were .?. sent to invessstigate \n thhehh stran... trans...mision \n Don't forget you shoot with space. \n and move with arrows. \n (Press enter to start)", { 100, 400 }, 21, 1, WHITE);
                if (IsKeyPressed(KEY_ENTER))
                {
                    IsGameStarted = 1;
                    useShader = 1;
                }
            }
            else
            {

                movement(AstroPosX, AstroPosy);
                if (IsSound == 0)
                {
                    PlaySound(bgm);
                    IsSound = 1;
                }
                if (IsKeyPressed(KEY_SPACE) && IsShootingAllowed == 1) {
                    laser.active = true;
                    laser.x = AstroPosX + 25;
                    laser.y = AstroPosy;

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

                for (int i = 0; i < asteroids.size(); i++) {
                    updateAsteroid(asteroids[i], laser, particles, TextWindow);
                    drawAsteroid(asteroids[i], asteroid);
                }
                updateParticles(particles);
                drawParticles(particles);

                asteroids.erase(remove_if(asteroids.begin(), asteroids.end(), [](const Asteroid& a) { return !a.active; }), asteroids.end());
                if (points > 3)
                {
                    ShouldFightBoss = 1;
                }

            }
        }
        EndShaderMode();
        drawPoints(points);
        EndDrawing();

        auto end = chrono::steady_clock::now();
        auto diff = end - start;
        if (diff < chrono::milliseconds(16)) {
            this_thread::sleep_for(chrono::milliseconds(16) - diff);
        }
    }

    CloseWindow();
}