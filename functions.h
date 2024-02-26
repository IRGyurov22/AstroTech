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
void updateLaserParticles(std::vector<LaserParticle>& particles);
void updateAsteroid(Asteroid& asteroid, Laser& laser, std::vector<Particle>& particles, Texture2D TextWindow);
void updateParticles(std::vector<Particle>& particles);
void updateLaserPositionAndIntensity(const Laser& laser);
void updateBossLaser(BossLaser& bossLaser);
void updateBossLaserParticles(std::vector<BossLaserParticle>& particles);
void bossmovement(int& bossx);
void initgame();


#endif 
