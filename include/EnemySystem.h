#pragma once
#include "Enemy.h"
#include "Player.h"
#include <vector>
#include "ScalingSystem.h"
void HandleEnemySpawning(std::vector<Enemy>& enemies, int screenWidth, int screenHeight, const Player& player, float& spawnTimer, const ScalingParams& scaling);
void HandleEnemyAI(std::vector<Enemy>& enemies, float screenWidth, float screenHeight, const Player& player);
