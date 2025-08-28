#include "XPSystem.h"
#include "LevelUpUI.h"

void HandleXPAndLeveling(Player& player, std::vector<XPOrb>& xpOrbs) {
    UpdateXPOrbs(xpOrbs, {player.position.x + player.size.x/2, player.position.y + player.size.y/2}, player.xp, 25);
    if (!player.levelUpState && player.xp >= player.xpToLevel) {
        player.levelUpState = true;
        player.level++;
        player.xp -= player.xpToLevel;
        player.xpToLevel += 20;
    }
}

void HandleLevelUpUI(Player& player, bool& showLevelUp, std::vector<UpgradeOption>& currentUpgrades, int& upgradeSelection) {
    if (player.levelUpState && !showLevelUp) {
        currentUpgrades = GetRandomUpgrades(3);
        showLevelUp = true;
        upgradeSelection = 0;
    }
    if (showLevelUp) {
        ShowLevelUpUI(currentUpgrades, upgradeSelection);
        int selection = GetUpgradeSelection((int)currentUpgrades.size());
        if (selection >= 0 && selection < (int)currentUpgrades.size()) {
            ApplyUpgrade(currentUpgrades[selection].type, currentUpgrades[selection].value, player);
            player.levelUpState = false;
            showLevelUp = false;
        }
    }
}
