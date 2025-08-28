#include "LevelUpUI.h"
#include "Player.h"
#include <raylib.h>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include <random>

std::vector<UpgradeOption> GetRandomUpgrades(int num) {
    std::vector<UpgradeOption> pool = {
        {"+Health", "Increase max health by 2", UpgradeOption::HEALTH, 2},
        {"+Damage", "Increase bullet damage by 1", UpgradeOption::DAMAGE, 1},
        {"Faster Fire", "Reduce fire cooldown by 20%", UpgradeOption::FIRE_RATE, 0.8f}
    };
    static std::random_device rd;
    static std::mt19937 g(rd());
    std::shuffle(pool.begin(), pool.end(), g);
    std::vector<UpgradeOption> res;
    for (int i = 0; i < num && i < (int)pool.size(); ++i) res.push_back(pool[i]);
    return res;
}

void ShowLevelUpUI(const std::vector<UpgradeOption>& options, int selected) {
    DrawRectangle(100, 100, 600, 400, Fade(DARKGRAY, 0.95f));
    Font font = GetFontDefault();
    DrawTextEx(font, "Level Up! Choose an upgrade", {170, 120}, 32, 2, GOLD);
    for (int i = 0; i < (int)options.size(); ++i) {
        Color c = (i == selected) ? YELLOW : WHITE;
        DrawRectangle(140, 180 + i*90, 520, 80, (i == selected) ? Fade(LIGHTGRAY,0.8f) : Fade(GRAY,0.5f));
        DrawTextEx(font, options[i].name.c_str(), {(float)160, (float)(200 + i*90)}, 28, 2, c);
        DrawTextEx(font, options[i].description.c_str(), {(float)160, (float)(230 + i*90)}, 20, 2, c);
    }
    DrawTextEx(font, "Use [1]/[2]/[3] or [Up]/[Down] + [Enter]", {180, 480}, 20, 2, WHITE);
}

int GetUpgradeSelection(int numOptions) {
    static int selected = 0;
    if (IsKeyPressed(KEY_ONE)) return 0;
    if (IsKeyPressed(KEY_TWO) && numOptions > 1) return 1;
    if (IsKeyPressed(KEY_THREE) && numOptions > 2) return 2;
    if (IsKeyPressed(KEY_UP)) selected = (selected + numOptions - 1) % numOptions;
    if (IsKeyPressed(KEY_DOWN)) selected = (selected + 1) % numOptions;
    if (IsKeyPressed(KEY_ENTER)) return selected;
    return -1;
}

void ApplyUpgrade(UpgradeOption::Type type, float value, Player& player) {
    switch(type) {
        case UpgradeOption::HEALTH:
            player.health += (int)value;
            break;
        case UpgradeOption::DAMAGE:
            player.damage += value;
            break;
        case UpgradeOption::FIRE_RATE:
            player.attackRate *= value;
            break;
        case UpgradeOption::SPEED:
            player.speed += value;
            break;
    }
}


