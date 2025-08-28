#include "ScalingSystem.h"

ScalingParams GetScalingParams(float timeSurvived, int playerLevel) {
    ScalingParams params;
    params.enemySpeed = 2.0f + timeSurvived * 0.05f + playerLevel * 0.1f;
    params.spawnInterval = 2.0f - timeSurvived * 0.015f - playerLevel * 0.03f;
    if (params.spawnInterval < 0.4f) params.spawnInterval = 0.4f;
    params.maxEnemies = 8 + static_cast<int>(timeSurvived / 10.0f) + playerLevel / 2;
    params.baseHealth = 1 + static_cast<int>(timeSurvived / 30.0f) + playerLevel / 3;
    params.baseXP = 5 + static_cast<int>(timeSurvived / 20.0f) + playerLevel / 2;
    return params;
}
