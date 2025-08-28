#pragma once
#include <string>
#include <vector>

struct UpgradeOption {
    std::string name;
    std::string description;
    enum Type { HEALTH, DAMAGE, FIRE_RATE, SPEED } type;
    float value;
};

void ShowLevelUpUI(const std::vector<UpgradeOption>& options, int selected);
int GetUpgradeSelection(int numOptions);
std::vector<UpgradeOption> GetRandomUpgrades(int num);
void ApplyUpgrade(UpgradeOption::Type type, float value, struct Player& player);
