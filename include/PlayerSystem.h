#pragma once
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include <vector>

void HandlePlayerInput(Player& player, float delta);
void HandlePlayerShooting(Player& player, std::vector<Bullet>& bullets, float& shootTimer, const std::vector<Enemy>& enemies);
void HandlePlayerStats(Player& player);
