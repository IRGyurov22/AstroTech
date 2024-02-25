#ifndef FUNCTIONS_H
#define FUNCTIONS_H

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

void movement(int& sposx, int& sposy);

void updateLaser(Laser& laser);

void drawLaser(Laser& laser);

void updateLaserParticles(vector<LaserParticle>& particles);

void drawLaserParticles(const vector<LaserParticle>& particles);

void updateAsteroid(Asteroid& asteroid, Laser& laser, vector<Particle>& particles);

void drawAsteroid(const Asteroid& asteroid);

void updateParticles(vector<Particle>& particles);

void drawParticles(const vector<Particle>& particles);

void updateLaserPositionAndIntensity(const Laser& laser);

void drawPoints(int points);

void initgame();

#endif 
