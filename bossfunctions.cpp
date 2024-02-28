#include "bossfunctions.h"
#include "raylib.h"
#include "draws.h"
#include "functions.h"

// Update the boss laser.
void updateBossLaser(BossLaser& bossLaser) {
    if (bossLaser.active) {
        bossLaser.y += 25;
        if (bossLaser.y >= 800) {
            bossLaser.active = false;
        }
    }
}

// Update the boss laser particles.
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

// Update the boss shooting.
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

// Implament the boss movement.
void bossmovement(int& bossx)
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

// When the laser hit the box.
void HandleLaserBossCollision(Laser& laser, int& bossHealth, int bossx) {
    if (laser.active) {
        Rectangle laserRect = { laser.x, laser.y, 5, 10 };
        Rectangle bossRect = { bossx, 50, 500, 250 };

        if (CheckCollisionRecs(laserRect, bossRect)) {
            bossHealth--;
            laser.active = false;
            laser.y = 1000;
        }
    }
}

// When the player was hitted by the boss's laser.
void HandlePlayerHitByBossLaser(int& AstroPosX, int& AstroPosy, BossLaser bossLaser,bool& EndGame) {
    Rectangle playerRect = { AstroPosX, AstroPosy, 100, 80 };
    Rectangle laserRect = { bossLaser.x, bossLaser.y, 20, 50 };

    if (CheckCollisionRecs(playerRect, laserRect)) {
        EndGame = 1;
    }
}