#pragma once
#include <vector>

struct ScalingParams {
    float enemySpeed;
    float spawnInterval;
    int maxEnemies;
    int baseHealth;
    int baseXP;
};

ScalingParams GetScalingParams(float timeSurvived, int playerLevel);
