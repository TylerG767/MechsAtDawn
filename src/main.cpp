#include "../include/Player.h"
#include "../include/Bullet.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "XPOrb.h"
#include "LevelUpUI.h"
#include "PlayerSystem.h"
#include "EnemySystem.h"
#include "XPSystem.h"
#include "CollisionSystem.h"
#include <raylib.h>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <algorithm>

void DrawHUD(const Player& player, int score = 0) {
    Font font = GetFontDefault();
    DrawTextEx(font, "Mechs At Dawn Prototype", { 180, 10 }, 32, 2, DARKGRAY);
    char healthText[32];
    snprintf(healthText, sizeof(healthText), "Health: %d", player.health);
    DrawTextEx(font, healthText, { 10, 560 }, 24, 2, DARKGREEN);
    char scoreText[32];
    snprintf(scoreText, sizeof(scoreText), "Score: %d", score);
    DrawTextEx(font, scoreText, { 650, 10 }, 24, 2, DARKBLUE);
}

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Mechs At Dawn");
    SetTargetFPS(60);
    Player player;
    InitPlayer(player);
    player.xp = 0;
    player.level = 1;
    player.xpToLevel = 20;
    player.levelUpState = false;

    std::vector<Bullet> bullets;
    std::vector<Enemy> enemies;
    std::vector<XPOrb> xpOrbs;
    int score = 0;

    // Enemy sprite
    Texture2D enemyTexture = LoadTexture("../assets/models/enemyShips.png");
    srand((unsigned int)time(0));
    
    // Wave system
    float spawnTimer = 0.0f;
    float timeSurvived = 0.0f;
    std::vector<UpgradeOption> currentUpgrades;
    bool showLevelUp = false;
    int upgradeSelection = 0;

    // Adjustable cooldown in seconds
    const float SHOOT_COOLDOWN = 0.2f; // 0.2 seconds between shots
    float shootTimer = 0.0f;

    bool gameOver = false;
    while (!WindowShouldClose() && !gameOver) {
        if (player.levelUpState && !showLevelUp) {
            currentUpgrades = GetRandomUpgrades(3);
            showLevelUp = true;
            upgradeSelection = 0;
        }

        float delta = GetFrameTime();
        timeSurvived += delta;
        ScalingParams scaling = GetScalingParams(timeSurvived, player.level);
        if (!showLevelUp) {
            HandlePlayerInput(player, delta);
            HandlePlayerShooting(player, bullets, shootTimer, enemies);
            UpdateBullets(bullets, 600.0f);
            HandleEnemySpawning(enemies, screenWidth, screenHeight, player, spawnTimer, scaling);
            HandleEnemyAI(enemies, (float)screenWidth, (float)screenHeight, player);
            HandleCollisions(player, enemies, bullets, score, xpOrbs);
            HandleXPAndLeveling(player, xpOrbs);
        }
        HandleLevelUpUI(player, showLevelUp, currentUpgrades, upgradeSelection);

        // Handle level up
        if (!player.levelUpState && player.xp >= player.xpToLevel) {
            player.levelUpState = true;
            player.level++;
            player.xp -= player.xpToLevel;
            player.xpToLevel += 20;
        }
        if (player.levelUpState && IsKeyPressed(KEY_ENTER)) {
            player.levelUpState = false;
        }


        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawHUD(player, score);
        // Show time survived
        Font font = GetFontDefault();
        char timeText[32];
        snprintf(timeText, sizeof(timeText), "Time: %.1f s", timeSurvived);
        DrawTextEx(font, timeText, { 10, 10 }, 24, 2, DARKGRAY);
        DrawPlayer(player);
        DrawBullets(bullets);
        DrawEnemies(enemies, enemyTexture);
        DrawXPOrbs(xpOrbs);
        // Show XP and level
        char xpText[64];
        snprintf(xpText, sizeof(xpText), "XP: %d / %d   Level: %d", player.xp, player.xpToLevel, player.level);
        DrawTextEx(font, xpText, { 10, 40 }, 24, 2, BLUE);
        if (showLevelUp) {
            ShowLevelUpUI(currentUpgrades, upgradeSelection);
            int selection = GetUpgradeSelection((int)currentUpgrades.size());
            if (selection >= 0 && selection < (int)currentUpgrades.size()) {
                ApplyUpgrade(currentUpgrades[selection].type, currentUpgrades[selection].value, player);
                player.levelUpState = false;
                showLevelUp = false;
            }
        }
        if (player.health <= 0) {
            DrawTextEx(font, "GAME OVER", { 260, 280 }, 48, 2, RED);
            gameOver = true;
        }
        EndDrawing();
    }

    UnloadTexture(enemyTexture);
    UnloadPlayer(player);
    CloseWindow();
    return 0;
}
