#include "functions.h"
#include "raylib.h"
#include "Draws.h"
#include "Update.h"
#include <chrono>
#include <thread>
#include <string>

void drawLaser(const Laser& laser) {
    if (laser.active) {
        DrawRectangle(laser.x + 21, laser.y, 5, 20, BLANK);
    }
}

void drawLaserParticles(const std::vector<LaserParticle>& particles) {
    for (const auto& particle : particles) {
        if (particle.active) {
            DrawCircle(particle.position.x, particle.position.y, particle.radius, particle.color);
        }
    }
}

void drawBossLaser(const BossLaser& bossLaser) {
    if (bossLaser.active) {
        DrawRectangle(bossLaser.x, bossLaser.y, 20, 50, BLANK);
    }
}

void drawBossLaserParticles(const std::vector<BossLaserParticle>& particles) {
    for (const auto& particle : particles) {
        if (particle.active) {
            DrawCircle(particle.position.x, particle.position.y, particle.radius, particle.color);
        }
    }
}

void drawAsteroid(const Asteroid& asteroid, Texture2D texture) {
    if (asteroid.active) {
        DrawTexture(texture, asteroid.x, asteroid.y, WHITE);
    }
}

void drawParticles(const std::vector<Particle>& particles) {
    for (const auto& particle : particles) {
        if (particle.active) {
            DrawCircle(static_cast<int>(particle.position.x), static_cast<int>(particle.position.y), particle.radius, particle.color);
        }
    }
}

void drawPoints(int points) {
    std::string pointsStr = std::to_string(points);
    DrawText(("Score: " + pointsStr).c_str(), 0, 0, 20, WHITE);
}
