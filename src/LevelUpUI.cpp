#include "LevelUpUI.h"
#include "Player.h"
#include <raylib.h>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include <random>
#include "RenderUtils.h" // for font helper

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
    Font font = RenderUtils::GetDefaultFont();
    float scale = RenderUtils::GetUIScale();
    
    // Responsive dialog box - centered with scaled dimensions
    int dialogWidth = (int)(600 * scale);
    int dialogHeight = (int)(400 * scale);
    Vector2 dialogPos = RenderUtils::GetRelativePosition(0.5f, 0.5f);
    dialogPos.x -= dialogWidth * 0.5f;
    dialogPos.y -= dialogHeight * 0.5f;
    
    DrawRectangle((int)dialogPos.x, (int)dialogPos.y, dialogWidth, dialogHeight, Fade(DARKGRAY, 0.95f));
    
    // Title - scaled and positioned relative to dialog
    float titleFontSize = RenderUtils::GetScaledFontSize(32);
    Vector2 titlePos = { dialogPos.x + dialogWidth * 0.1f, dialogPos.y + 20 * scale };
    DrawTextEx(font, "Level Up! Choose an upgrade", titlePos, titleFontSize, 2, GOLD);
    
    // Options - scaled spacing and positioning
    float optionSpacing = 90 * scale;
    float optionHeight = 80 * scale;
    float optionWidth = dialogWidth * 0.85f;
    
    for (int i = 0; i < (int)options.size(); ++i) {
        Color c = (i == selected) ? YELLOW : WHITE;
        Color bgColor = (i == selected) ? Fade(LIGHTGRAY, 0.8f) : Fade(GRAY, 0.5f);
        
        Vector2 optionPos = { dialogPos.x + dialogWidth * 0.075f, dialogPos.y + 80 * scale + i * optionSpacing };
        DrawRectangle((int)optionPos.x, (int)optionPos.y, (int)optionWidth, (int)optionHeight, bgColor);
        
        float nameFontSize = RenderUtils::GetScaledFontSize(28);
        float descFontSize = RenderUtils::GetScaledFontSize(20);
        
        Vector2 namePos = { optionPos.x + 20 * scale, optionPos.y + 20 * scale };
        Vector2 descPos = { optionPos.x + 20 * scale, optionPos.y + 50 * scale };
        
        DrawTextEx(font, options[i].name.c_str(), namePos, nameFontSize, 2, c);
        DrawTextEx(font, options[i].description.c_str(), descPos, descFontSize, 2, c);
    }
    
    // Instructions - bottom of dialog
    float instrFontSize = RenderUtils::GetScaledFontSize(20);
    Vector2 instrPos = { dialogPos.x + dialogWidth * 0.1f, dialogPos.y + dialogHeight - 40 * scale };
    DrawTextEx(font, "Use [1]/[2]/[3] or [Up]/[Down] + [Enter]", instrPos, instrFontSize, 2, WHITE);
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


