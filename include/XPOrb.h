#pragma once
#include "raylib.h"
#include <vector>
struct XPOrb {
    Vector2 position;
    int value;
};
void SpawnXPOrb(std::vector<XPOrb>& orbs, Vector2 pos, int value);
void UpdateXPOrbs(std::vector<XPOrb>& orbs, Vector2 playerPos, int& playerXP, int pickupRadius);
void DrawXPOrbs(const std::vector<XPOrb>& orbs);
