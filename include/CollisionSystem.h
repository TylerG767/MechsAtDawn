#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include <vector>

#include "XPOrb.h"
void HandleCollisions(Player& player, std::vector<Enemy>& enemies, std::vector<Bullet>& bullets, int& score, std::vector<XPOrb>& xpOrbs);
