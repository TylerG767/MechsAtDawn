#include "EnemySystem.h"
#include <cstdlib>
#include <algorithm>
#include <cmath>

#include "ScalingSystem.h"

void HandleEnemySpawning(std::vector<Enemy>& enemies, int screenWidth, int screenHeight, const Player& player, float& spawnTimer, const ScalingParams& scaling) {
    spawnTimer -= GetFrameTime();
    if (spawnTimer <= 0.0f && enemies.size() < (size_t)scaling.maxEnemies) {
        float minSpawnRadius = 120.0f;
        SpawnEnemy(enemies, screenWidth, screenHeight, player.position, minSpawnRadius, scaling.enemySpeed, scaling);
        spawnTimer = scaling.spawnInterval;
    }
}

void HandleEnemyAI(std::vector<Enemy>& enemies, float screenWidth, float screenHeight, const Player& player) {
    UpdateEnemies(enemies, screenWidth, screenHeight, player.position);
}
