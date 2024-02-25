#include "functions.h"
#include "raylib.h"
#include <chrono>
#include <thread>
#include <string>
#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION            330
#else   
#define GLSL_VERSION            100
#endif


int windowsHeight = 850;
int windowsWidth = 800;

bool IsGameStarted = 0;
bool ShouldFightBoss = 1;

Rectangle answear1 = { 150, 400, 200, 50 };
Rectangle answear2 = { 150, 440, 200, 50 };
Rectangle answear3 = { 150, 465, 200, 50 };
Rectangle answear4 = { 150, 490, 200, 50 };

int laserspeed = 7;
int movementSpeed = 4;
int asteroidspeed = 2;

bool IsQuestionAnsweared = 0;
int AsteroidSpawnTime = 4;

int points = 0;

bool IsSound = 0;
bool IsShootingAllowed = 1;
bool useShader = 1;

int QuestionNumber = GetRandomValue(1, 12);

Vector2 laserPosition = { 0, 0 };
float laserIntensity = 0.0f;
Vector3 laserColor = { 1.0f, 0.0f, 0.0f };

void initsettings()
{

}

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
        DrawRectangle(laser.x + 21, laser.y, 5, 20, BLANK);
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

void updateAsteroid(Asteroid& asteroid, Laser& laser, vector<Particle>& particles, Texture2D TextWindow) {
    if (asteroid.active) {
        asteroid.y += asteroidspeed;

        if (CheckCollisionRecs({ (float)laser.x, (float)laser.y, 5, 20 }, { (float)asteroid.x - asteroid.size / 2, (float)asteroid.y - asteroid.size / 2, (float)asteroid.size, (float)asteroid.size })) {


            DrawTexture(TextWindow, 0, 75, GRAY);
            useShader = 0;
            laserspeed = 0;
            movementSpeed = 0;
            asteroidspeed = 0;
            AsteroidSpawnTime = 999999;
            IsShootingAllowed = 0;
            
            
            switch (QuestionNumber)
            {
            case 1:
                DrawText("A projectile fired with initial velocity u at some angle 0 has a range R.\n If the initial velocity be doubled keeping the angle of projection same,\n then the range will be", 150, 325, 16, BLACK);
                DrawRectangleRec(answear1, BLANK);
                DrawText("R/2", 160, 415, 15, BLACK);
                DrawRectangleRec(answear2, BLANK);
                DrawText("4R", 160, 440, 15, BLACK);
                DrawRectangleRec(answear3, BLANK);
                DrawText("2R", 160, 465, 15, BLACK);
                DrawRectangleRec(answear4, BLANK);
                DrawText("None of the above", 160, 490, 15, BLACK);
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
                break;
            case 2:
                DrawText("Choose the incorrect statement from \n the following regarding magnetic lines of field -", 150, 325, 16, BLACK);
                DrawRectangleRec(answear1, BLANK);
                DrawText("The direction of magnetic field at a point is taken to be the direction in which \n the north Pole of a magnetic compass needle points.", 160, 415, 15, BLACK);
                DrawRectangleRec(answear2, BLANK);
                DrawText("Magnetlc field lines are closed curves.", 160, 450, 15, BLACK);
                DrawRectangleRec(answear3, BLANK);
                DrawText("If magnetic field lines are parallel and equidistant, they represent \n zero field strength.", 160, 475, 15, BLACK);
                DrawRectangleRec(answear4, BLANK);
                DrawText("None of the above", 160, 520, 15, BLACK);
                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear1))
                {
                    IsQuestionAnsweared = 1;
                }
                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear2))
                {
                    IsQuestionAnsweared = 1;
                }
                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear3))
                {
                    IsQuestionAnsweared = 1;
                    points++;
                }
                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear4))
                {
                    IsQuestionAnsweared = 1;
                }
                break;
            case 3:
                DrawText("What type of waves are light wave?", 150, 325, 16, BLACK);
                DrawRectangleRec(answear1, BLANK);
                DrawText("Transverse wave", 160, 425, 15, BLACK);
                DrawRectangleRec(answear2, BLANK);
                DrawText("Longitudinal wave", 160, 460, 15, BLACK);
                DrawRectangleRec(answear3, BLANK);
                DrawText("Both A & B", 160, 485, 15, BLACK);
                DrawRectangleRec(answear4, BLANK);
                DrawText("None", 160, 510, 15, BLACK);
                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear1))
                {
                    IsQuestionAnsweared = 1;
                    points++;
                }
                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear2))
                {
                    IsQuestionAnsweared = 1;
                }
                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear3))
                {
                    IsQuestionAnsweared = 1;
                }
                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear4))
                {
                    IsQuestionAnsweared = 1;
                }
                    break;
            case 4:
                DrawText("A 220 V, 100 W bulb is connected to a 110 V source. \n Calculate the power consumed by the bulb.", 150, 325, 16, BLACK);
                DrawRectangleRec(answear1, BLANK);
                DrawText("10W", 160, 425, 15, BLACK);
                DrawRectangleRec(answear2, BLANK);
                DrawText("15W", 160, 460, 15, BLACK);
                DrawRectangleRec(answear3, BLANK);
                DrawText("20W", 160, 485, 15, BLACK);
                DrawRectangleRec(answear4, BLANK);
                DrawText("25W", 160, 510, 15, BLACK);
                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear1))
                {
                    IsQuestionAnsweared = 1;
                }
                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear2))
                {
                    IsQuestionAnsweared = 1;
                }
                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear3))
                {
                    IsQuestionAnsweared = 1;
                }
                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear4))
                {
                    IsQuestionAnsweared = 1;
                    points++;
                }
                break;
            case 5:
                DrawText("The instrument _________ is used for detecting electric current is", 150, 350, 16, BLACK);
                DrawRectangleRec(answear1, BLANK);
                DrawText("Galvanometer", 160, 425, 15, BLACK);
                DrawRectangleRec(answear2, BLANK);
                DrawText("Tube tester", 160, 460, 15, BLACK);
                DrawRectangleRec(answear3, BLANK);
                DrawText("Altimeter", 160, 485, 15, BLACK);
                DrawRectangleRec(answear4, BLANK);
                DrawText("Fathometer", 160, 510, 15, BLACK);
                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear1))
                {
                    IsQuestionAnsweared = 1;
                    points++;
                }
                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear2))
                {
                    IsQuestionAnsweared = 1;
                }
                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear3))
                {
                    IsQuestionAnsweared = 1;
                }
                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear4))
                {
                    IsQuestionAnsweared = 1;
                }
                break;
            case 6:
                DrawText("The instrument _________ is used for detecting electric current is", 150, 350, 16, BLACK);
                DrawRectangleRec(answear1, BLANK);
                DrawText("Galvanometer", 160, 425, 15, BLACK);
                DrawRectangleRec(answear2, BLANK);
                DrawText("Tube tester", 160, 460, 15, BLACK);
                DrawRectangleRec(answear3, BLANK);
                DrawText("Altimeter", 160, 485, 15, BLACK);
                DrawRectangleRec(answear4, BLANK);
                DrawText("Fathometer", 160, 510, 15, BLACK);
                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear1))
                {
                    IsQuestionAnsweared = 1;
                    points++;
                }
                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear2))
                {
                    IsQuestionAnsweared = 1;
                }
                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear3))
                {
                    IsQuestionAnsweared = 1;
                }
                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear4))
                {
                    IsQuestionAnsweared = 1;
                }
                break;
            case 7:
                DrawText("How much work is done in moving a charge of 5 C across two \n points having a potential difference of 16 V?", 150, 350, 16, BLACK);
                DrawRectangleRec(answear1, BLANK);
                DrawText("65 J", 160, 425, 15, BLACK);
                DrawRectangleRec(answear2, BLANK);
                DrawText("45 J", 160, 460, 15, BLACK);
                DrawRectangleRec(answear3, BLANK);
                DrawText("40 J", 160, 485, 15, BLACK);
                DrawRectangleRec(answear4, BLANK);
                DrawText("80 J", 160, 510, 15, BLACK);
                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear1))
                {
                    IsQuestionAnsweared = 1;
                }
                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear2))
                {
                    IsQuestionAnsweared = 1;
                }
                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear3))
                {
                    IsQuestionAnsweared = 1;
                }
                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear4))
                {
                    IsQuestionAnsweared = 1;
                    points++;
                }
                break;
            case 8:
                DrawText("'Decibel' is the unit used for measuring :-", 150, 350, 16, BLACK);
                DrawRectangleRec(answear1, BLANK);
                DrawText("Speed of light", 160, 425, 15, BLACK);
                DrawRectangleRec(answear2, BLANK);
                DrawText("Itensity of sound", 160, 460, 15, BLACK);
                DrawRectangleRec(answear3, BLANK);
                DrawText("Itensity of heat", 160, 485, 15, BLACK);
                DrawRectangleRec(answear4, BLANK);
                DrawText("Itensity of earthquake", 160, 510, 15, BLACK);
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
                break;
            case 9:
                DrawText("Rod and cone are found in:", 150, 350, 16, BLACK);
                DrawRectangleRec(answear1, BLANK);
                DrawText("Heart", 160, 425, 15, BLACK);
                DrawRectangleRec(answear2, BLANK);
                DrawText("Eyes", 160, 460, 15, BLACK);
                DrawRectangleRec(answear3, BLANK);
                DrawText("Lungs", 160, 485, 15, BLACK);
                DrawRectangleRec(answear4, BLANK);
                DrawText("None of the above", 160, 510, 15, BLACK);
                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear1))
                {
                    IsQuestionAnsweared = 1;
                }
                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear2))
                {
                    IsQuestionAnsweared = 1;
                }
                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear3))
                {
                    IsQuestionAnsweared = 1;
                    points++;
                }
                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear4))
                {
                    IsQuestionAnsweared = 1;
                }
                break;
            case 10:
                DrawText("A passenger in a moving bus is thrown forward when the bus suddenly stops. This is explained", 150, 350, 16, BLACK);
                DrawRectangleRec(answear1, BLANK);
                DrawText("by Newton's first law", 160, 425, 15, BLACK);
                DrawRectangleRec(answear2, BLANK);
                DrawText("by Newton's second law", 160, 460, 15, BLACK);
                DrawRectangleRec(answear3, BLANK);
                DrawText("by Newton's third law", 160, 485, 15, BLACK);
                DrawRectangleRec(answear4, BLANK);
                DrawText("by the principle of conservation of momentum", 160, 510, 15, BLACK);
                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear1))
                {
                    IsQuestionAnsweared = 1;
                    points++;
                }
                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear2))
                {
                    IsQuestionAnsweared = 1;
                }
                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear3))
                {
                    IsQuestionAnsweared = 1;
                }
                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear4))
                {
                    IsQuestionAnsweared = 1;
                }
                break;
            case 11:
                DrawText("At which point of the Earth is there no gravity?", 150, 350, 16, BLACK);
                DrawRectangleRec(answear1, BLANK);
                DrawText("At North and South Pole", 160, 425, 15, BLACK);
                DrawRectangleRec(answear2, BLANK);
                DrawText("At equator", 160, 460, 15, BLACK);
                DrawRectangleRec(answear3, BLANK);
                DrawText("On the ocean surface", 160, 485, 15, BLACK);
                DrawRectangleRec(answear4, BLANK);
                DrawText("At centre of the Earth", 160, 510, 15, BLACK);
                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear1))
                {
                    IsQuestionAnsweared = 1;
                }
                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear2))
                {
                    IsQuestionAnsweared = 1;
                }
                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear3))
                {
                    IsQuestionAnsweared = 1;
                }
                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear4))
                {
                    IsQuestionAnsweared = 1;
                    points++;
                }
                break;
            case 12:
                DrawText("Which of the following space agencies uses a spacecraft named Hayabusa ?", 150, 350, 16, BLACK);
                DrawRectangleRec(answear1, BLANK);
                DrawText(" National Aeronautics and Space Administration(NASA)", 160, 425, 15, BLACK);
                DrawRectangleRec(answear2, BLANK);
                DrawText("Centre national detudes spatiales (CNES)", 160, 460, 15, BLACK);
                DrawRectangleRec(answear3, BLANK);
                DrawText("China National Space Administration (CNSA)", 160, 485, 15, BLACK);
                DrawRectangleRec(answear4, BLANK);
                DrawText("Japan Aerospace Exploration Agency (JAXA)", 160, 510, 15, BLACK);
                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear1))
                {
                    IsQuestionAnsweared = 1;
                }
                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear2))
                {
                    IsQuestionAnsweared = 1;
                }
                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear3))
                {
                    IsQuestionAnsweared = 1;
                }
                if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && CheckCollisionPointRec(GetMousePosition(), answear4))
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
                QuestionNumber = GetRandomValue(1, 12);
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
    laserPosition.x = laser.x - 25;
    laserPosition.y = laser.y;
    laserIntensity = 5.0;
    if (laserPosition.y <= 0)
    {
        laserPosition.y = 1000;
        laserPosition.x = 1000;
    }
}
void updateBossLaserPositionAndIntensity(const BossLaser& bossLaser) {
    laserPosition.x = bossLaser.x - 25;
    laserPosition.y = bossLaser.y;
    laserIntensity = 25.0;
    if (laserPosition.y >= 800) {
        laserPosition.y = 5000;
        laserPosition.x = 5000;
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

void drawBossLaser(const BossLaser& bossLaser) {
    if (bossLaser.active) {
        DrawRectangle(bossLaser.x + 21, bossLaser.y, 5, 20, BLANK);
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

void drawBossLaserParticles(const std::vector<BossLaserParticle>& particles) {
    for (const auto& particle : particles) {
        if (particle.active) {
            DrawCircle(particle.position.x, particle.position.y, particle.radius, particle.color);
        }
    }
}

void drawPoints(int points) {
    std::string pointsStr = std::to_string(points);
    DrawText(("Score: " + pointsStr).c_str(), 0, 0, 20, WHITE);
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

    SetTargetFPS(60);
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
        if (useShader == 1)
        {
            BeginShaderMode(lighting);

            updateLaserPositionAndIntensity(laser);

            SetShaderValue(lighting, GetShaderLocation(lighting, "lightPos"), &laserPosition, SHADER_UNIFORM_VEC2);
            SetShaderValue(lighting, GetShaderLocation(lighting, "lightIntensity"), &laserIntensity, SHADER_UNIFORM_FLOAT);
            SetShaderValue(lighting, GetShaderLocation(lighting, "lightColor"), &laserColor, SHADER_UNIFORM_VEC3);

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
                    BeginShaderMode(lighting);
                    updateLaserPositionAndIntensity(laser);
                    
                    SetShaderValue(lighting, GetShaderLocation(lighting, "lightPos"), &laserPosition, SHADER_UNIFORM_VEC2);
                    SetShaderValue(lighting, GetShaderLocation(lighting, "lightIntensity"), &laserIntensity, SHADER_UNIFORM_FLOAT);
                    SetShaderValue(lighting, GetShaderLocation(lighting, "lightColor"), &laserColor, SHADER_UNIFORM_VEC3);
                    EndShaderMode();
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