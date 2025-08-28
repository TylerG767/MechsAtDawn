#ifndef ENEMY_H
#define ENEMY_H
#include <vector>
#include "raylib.h"
#include "ScalingSystem.h"

struct Enemy {
    Vector2 position;
    Vector2 direction;
    float speed;
    Vector2 size;
    int health;
    int enemyType; // 0 = left half, 1 = right half
    float pathOffsetAngle; // for random pathing
    int xpValue; // XP granted when killed
};

void SpawnEnemy(std::vector<Enemy>& enemies, int screenWidth, int screenHeight, Vector2 playerPos, float minSpawnRadius, float speed, const ScalingParams& scaling);
void UpdateEnemies(std::vector<Enemy>& enemies, float screenWidth, float screenHeight, Vector2 playerPos);
void DrawEnemies(const std::vector<Enemy>& enemies, Texture2D enemyTexture);

#endif // ENEMY_H
