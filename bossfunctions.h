#pragma once
#include <vector>
struct Laser;
struct LaserParticle;
struct BossLaser;
struct BossLaserParticle;
struct Asteroid;
struct Particle;

void HandleLaserBossCollision(Laser& laser, int& bossHealth, int bossx);

void updateBossLaser(BossLaser& bossLaser);

void HandleLaserBossCollision(Laser& laser, int& bossHealth, int bossx);

void bossmovement(int& bossx);

void bossShoot(std::vector<LaserParticle>& laserParticles, int bossx);

float smooth(float a, float b, float t);

void updateBossLaserParticles(std::vector<BossLaserParticle>& particles);

void HandlePlayerHitByBossLaser(int& AstroPosX, int& AstroPosy, BossLaser bossLaser, bool& EndGame);



