#include "XPOrb.h"
#include <vector>
#include <raylib.h>
#include <algorithm>
#include <cmath>
#include "MathUtils.h" // for distance calculations

void SpawnXPOrb(std::vector<XPOrb>& orbs, Vector2 pos, int value) {
    XPOrb orb;
    orb.position = pos;
    orb.value = value;
    orbs.push_back(orb);
}

void UpdateXPOrbs(std::vector<XPOrb>& orbs, Vector2 playerPos, int& playerXP, int pickupRadius) {
    orbs.erase(std::remove_if(orbs.begin(), orbs.end(), [&](XPOrb& orb) {
        float dist = MathUtils::Distance(orb.position, playerPos);
        if (dist <= pickupRadius) {
            playerXP += orb.value;
            return true; // Remove orb
        }
        return false;
    }), orbs.end());
}

void DrawXPOrbs(const std::vector<XPOrb>& orbs) {
    for (const auto& orb : orbs) {
        DrawCircleV(orb.position, 6, ORANGE);
    }
}
