#include "functions.h"
#include "raylib.h"
#include "Draws.h"
#include <chrono>
#include <thread>
#include <string>

// Draw the laser.
void drawLaser(const Laser& laser) {
    if (laser.active) {
        DrawRectangle(laser.x + 21, laser.y, 5, 20, BLANK);
    }
}

// Draw the laser particles.
void drawLaserParticles(const std::vector<LaserParticle>& particles) {
    for (const auto& particle : particles) {
        if (particle.active) {
            DrawCircle(particle.position.x, particle.position.y, particle.radius, particle.color);
        }
    }
}

// Draw the boss laser.
void drawBossLaser(const BossLaser& bossLaser) { 
    if (bossLaser.active) {
        DrawRectangle(bossLaser.x, bossLaser.y+25, 20, 50, BLANK);
    }
}

// Draw the boss laser particles.
void drawBossLaserParticles(const std::vector<BossLaserParticle>& particles) {
    for (const auto& particle : particles) {
        if (particle.active) {
            DrawCircle(particle.position.x, particle.position.y, particle.radius, particle.color);
        }
    }
}

// Draw the asteroid.
void drawAsteroid(const Asteroid& asteroid, Texture2D texture) {
    if (asteroid.active) {
        DrawTexture(texture, asteroid.x, asteroid.y, WHITE);
    }
}

// Draw the particles.
void drawParticles(const std::vector<Particle>& particles) {
    for (const auto& particle : particles) {
        if (particle.active) {
            DrawCircle(static_cast<int>(particle.position.x), static_cast<int>(particle.position.y), particle.radius, particle.color);
        }
    }
}

// Draw the points.
void drawPoints(int points) {
    std::string pointsStr = std::to_string(points);
    DrawText(("Score: " + pointsStr).c_str(), 0, 0, 20, WHITE);
}