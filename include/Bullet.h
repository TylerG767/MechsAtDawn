#ifndef BULLET_H
#define BULLET_H

#include <vector>
#include "raylib.h"

struct Bullet {
    Vector2 position;
    Vector2 velocity;
    float width, height;
    float damage;
    bool active;
};

void SpawnBullet(std::vector<Bullet>& bullets, const Vector2& spawnPos, const Vector2& direction, float damage);
void SpawnBullet(std::vector<Bullet>& bullets, const Vector2& spawnPos, float damage);
void UpdateBullets(std::vector<Bullet>& bullets, float screenHeight);
void DrawBullets(const std::vector<Bullet>& bullets);

#endif // BULLET_H
