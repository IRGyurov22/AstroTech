#pragma once

#include "raylib.h"
#include <vector>

using namespace std;


struct Laser {
    int x;
    int y;
    bool active;
};

struct Asteroid {
    int x;
    int y;
    int size;
    bool active;

};

struct Particle {
    Vector2 position;
    Vector2 velocity;
    Color color;
    int radius;
    bool active;
};

struct LaserParticle {
    Vector2 position;
    Vector2 velocity;
    Color color;
    int radius;
    int lifeSpan;
    bool active;
};

struct BossLaser {
    float x;
    float y;
    bool active;
};

struct BossLaserParticle {
    Vector2 position;
    Vector2 velocity;
    Color color;
    float radius;
    int lifeSpan;
    bool active;
};

void updateLaser(Laser& laser);

void updateLaserParticles(vector<LaserParticle>& particles);

void updateParticles(vector<Particle>& particles);

void updateLaserPositionAndIntensity(const Laser& laser);

void updateAsteroid(Asteroid& asteroid, Laser& laser, vector<Particle>& particles, Texture2D TextWindow);

void initgame();

