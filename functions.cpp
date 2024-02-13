#include "functions.h"

void movement(int& sposx, int& sposy) {
    if (IsKeyDown(KEY_RIGHT)) {
        sposx += 4;
    }
    if (IsKeyDown(KEY_LEFT)) {
        sposx -= 4;
    }
    if (IsKeyDown(KEY_UP)) {
        sposy -= 4;
    }
    if (IsKeyDown(KEY_DOWN)) {
        sposy += 4;
    }
}

void updateLaser(Laser& laser) {
    if (laser.active) {
        laser.y -= 7;

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
        asteroid.y += 2;

        if (CheckCollisionRecs({ (float)laser.x, (float)laser.y, 5, 20 }, { (float)asteroid.x - asteroid.size / 2, (float)asteroid.y - asteroid.size / 2, (float)asteroid.size, (float)asteroid.size })) {
            asteroid.active = false;
            laser.active = false;

            for (int i = 0; i < 30; ++i) {
                Particle particle;
                particle.position = { static_cast<float>(asteroid.x), static_cast<float>(asteroid.y) };
                particle.velocity = { static_cast<float>(GetRandomValue(-5, 5)), static_cast<float>(GetRandomValue(-5, 5)) };
                particle.color = WHITE;
                particle.radius = GetRandomValue(1, 3);
                particle.active = true;
                particles.push_back(particle);
            }
        }

        if (asteroid.y >= 800) {
            asteroid.active = false;
        }
    }
}

void drawAsteroid(const Asteroid& asteroid) {
    if (asteroid.active) {
        DrawCircle(asteroid.x, asteroid.y, asteroid.size / 2, WHITE);
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
