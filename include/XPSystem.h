#pragma once
#include "Player.h"
#include "XPOrb.h"
#include "LevelUpUI.h"
#include <vector>

void HandleXPAndLeveling(Player& player, std::vector<XPOrb>& xpOrbs);
void HandleLevelUpUI(Player& player, bool& showLevelUp, std::vector<UpgradeOption>& currentUpgrades, int& upgradeSelection);
