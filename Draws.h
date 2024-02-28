#pragma once

#include "functions.h"
#include "raylib.h"
#include "Draws.h"
#include <chrono>
#include <thread>
#include <string>


struct Laser;
struct LaserParticle;
struct BossLaser;
struct BossLaserParticle;
struct Asteroid;
struct Particle;

void drawLaser(const Laser& laser);
void drawLaserParticles(const std::vector<LaserParticle>& particles);
void drawBossLaser(const BossLaser& bossLaser);
void drawBossLaserParticles(const std::vector<BossLaserParticle>& particles);
void drawAsteroid(const Asteroid& asteroid, Texture2D texture);
void drawParticles(const std::vector<Particle>& particles);
void drawPoints(int points);

