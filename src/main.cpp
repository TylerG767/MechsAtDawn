#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "XPOrb.h"
#include "LevelUpUI.h"
#include "PlayerSystem.h"
#include "EnemySystem.h"
#include "XPSystem.h"
#include "CollisionSystem.h"
#include "game.h" // for Game class
#include "GameConfig.h" // for centralized configuration
#include "RenderUtils.h" // for rendering helpers
#include <raylib.h>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <algorithm>

void DrawHUD(const Player& player, int score = 0) {
    Font font = RenderUtils::GetDefaultFont();
    
    // Responsive title - centered at top
    float titleFontSize = RenderUtils::GetScaledFontSize(32);
    Vector2 titlePos = RenderUtils::GetRelativePosition(0.5f, 0.02f);
    Vector2 titleSize = MeasureTextEx(font, "Mechs At Dawn Prototype", titleFontSize, 2);
    titlePos.x -= titleSize.x * 0.5f; // Center horizontally
    DrawTextEx(font, "Mechs At Dawn Prototype", titlePos, titleFontSize, 2, DARKGRAY);
    
    // Health - bottom left
    char healthText[32];
    snprintf(healthText, sizeof(healthText), "Health: %d", player.health);
    float healthFontSize = RenderUtils::GetScaledFontSize(24);
    Vector2 healthPos = RenderUtils::GetEdgePosition(10, 0, -1, 40);
    DrawTextEx(font, healthText, healthPos, healthFontSize, 2, DARKGREEN);
    
    // Score - top right
    char scoreText[32];
    snprintf(scoreText, sizeof(scoreText), "Score: %d", score);
    float scoreFontSize = RenderUtils::GetScaledFontSize(24);
    Vector2 scoreSize = MeasureTextEx(font, scoreText, scoreFontSize, 2);
    Vector2 scorePos = RenderUtils::GetEdgePosition(0, 10, scoreSize.x + 10, -1);
    DrawTextEx(font, scoreText, scorePos, scoreFontSize, 2, DARKBLUE);
}

int main() {
    // Initialize adjustable screen dimensions
    // GameConfig::InitializeScreenSize(1024, 768); // Example: custom screen size
    GameConfig::InitializeScreenSize(); // Uses defaults (800x600)
    
    // Initialize window using centralized config
    SetConfigFlags(FLAG_WINDOW_RESIZABLE); // Enable window resizing
    InitWindow(GameConfig::SCREEN_WIDTH, GameConfig::SCREEN_HEIGHT, GameConfig::WINDOW_TITLE);
    SetTargetFPS(GameConfig::TARGET_FPS);
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
        
        // Handle window resizing
        if (IsWindowResized()) {
            GameConfig::UpdateScreenSize(GetScreenWidth(), GetScreenHeight());
        }
        
        ScalingParams scaling = GetScalingParams(timeSurvived, player.level);
        if (!showLevelUp) {
            HandlePlayerInput(player, delta); // Handles movement and clamping
            HandlePlayerShooting(player, bullets, shootTimer, enemies);
            UpdateBullets(bullets, (float)GameConfig::SCREEN_HEIGHT);
            HandleEnemySpawning(enemies, GameConfig::SCREEN_WIDTH, GameConfig::SCREEN_HEIGHT, player, spawnTimer, scaling);
            HandleEnemyAI(enemies, (float)GameConfig::SCREEN_WIDTH, (float)GameConfig::SCREEN_HEIGHT, player);
            HandleCollisions(player, enemies, bullets, score, xpOrbs);
            HandleXPAndLeveling(player, xpOrbs); // Handles XP, leveling, and triggers level up state
        }
        HandleLevelUpUI(player, showLevelUp, currentUpgrades, upgradeSelection);

        // Removed redundant XP/level up logic; now handled exclusively in HandleXPAndLeveling and HandleLevelUpUI.


        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawHUD(player, score);
        // Show time survived - top left
        Font font = RenderUtils::GetDefaultFont();
        char timeText[32];
        snprintf(timeText, sizeof(timeText), "Time: %.1f s", timeSurvived);
        float timeFontSize = RenderUtils::GetScaledFontSize(24);
        Vector2 timePos = RenderUtils::GetEdgePosition(10, 10, -1, -1);
        DrawTextEx(font, timeText, timePos, timeFontSize, 2, DARKGRAY);
        DrawPlayer(player);
        DrawBullets(bullets);
        DrawEnemies(enemies, enemyTexture);
        DrawXPOrbs(xpOrbs);
        // Show XP and level - below time
        char xpText[64];
        snprintf(xpText, sizeof(xpText), "XP: %d / %d   Level: %d", player.xp, player.xpToLevel, player.level);
        float xpFontSize = RenderUtils::GetScaledFontSize(24);
        Vector2 xpPos = RenderUtils::GetEdgePosition(10, 40 * RenderUtils::GetUIScale(), -1, -1);
        DrawTextEx(font, xpText, xpPos, xpFontSize, 2, BLUE);
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
            // Game Over - centered on screen
            float gameOverFontSize = RenderUtils::GetScaledFontSize(48);
            Vector2 gameOverPos = RenderUtils::GetRelativePosition(0.5f, 0.5f);
            Vector2 gameOverSize = MeasureTextEx(font, "GAME OVER", gameOverFontSize, 2);
            gameOverPos.x -= gameOverSize.x * 0.5f; // Center horizontally
            gameOverPos.y -= gameOverSize.y * 0.5f; // Center vertically
            DrawTextEx(font, "GAME OVER", gameOverPos, gameOverFontSize, 2, RED);
            gameOver = true;
        }
        EndDrawing();
    }

    UnloadTexture(enemyTexture);
    UnloadPlayer(player);
    CloseWindow(); // Cleanup window
    return 0;
}
