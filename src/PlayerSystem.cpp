#include "PlayerSystem.h"
#include <raylib.h>
#include "GameConfig.h" // for centralized screen dimensions
#include "MathUtils.h" // for vector operations

// Helper function to clamp player position inside window
static void ClampPlayerToWindow(Player& player, int screenWidth = -1, int screenHeight = -1) {
    // Use current screen dimensions if not specified
    if (screenWidth == -1) screenWidth = GameConfig::SCREEN_WIDTH;
    if (screenHeight == -1) screenHeight = GameConfig::SCREEN_HEIGHT;
    if (player.position.x < 0) player.position.x = 0;
    if (player.position.y < 0) player.position.y = 0;
    if (player.position.x > screenWidth - player.size.x) player.position.x = screenWidth - player.size.x;
    if (player.position.y > screenHeight - player.size.y) player.position.y = screenHeight - player.size.y;
}

void HandlePlayerInput(Player& player, float delta) {
    // Handle WASD movement
    if (IsKeyDown(KEY_W)) player.position.y -= player.speed;
    if (IsKeyDown(KEY_S)) player.position.y += player.speed;
    if (IsKeyDown(KEY_A)) player.position.x -= player.speed;
    if (IsKeyDown(KEY_D)) player.position.x += player.speed;
    // Clamp to window using helper
    ClampPlayerToWindow(player);
}

#include <limits>
#include <cmath>
#include "Enemy.h"

void HandlePlayerShooting(Player& player, std::vector<Bullet>& bullets, float& shootTimer, const std::vector<Enemy>& enemies) {
    if (shootTimer > 0.0f) shootTimer -= GetFrameTime();
    if (shootTimer <= 0.0f && !enemies.empty()) {
        // Find nearest enemy
        Vector2 playerCenter = { player.position.x + player.size.x / 2, player.position.y + player.size.y / 2 };
        float minDist = std::numeric_limits<float>::max();
        Vector2 targetPos = playerCenter;
        for (const auto& enemy : enemies) {
            Vector2 enemyCenter = { enemy.position.x + enemy.size.x / 2, enemy.position.y + enemy.size.y / 2 };
            float dx = enemyCenter.x - playerCenter.x;
            float dy = enemyCenter.y - playerCenter.y;
            float dist = dx*dx + dy*dy;
            if (dist < minDist) {
                minDist = dist;
                targetPos = enemyCenter;
            }
        }
        // Fire bullet toward nearest enemy
        Vector2 bulletSpawn = { player.position.x + player.size.x / 2 - 3, player.position.y + player.size.y / 2 - 8 };
        // This centers the bullet on the player
        Vector2 dir = { targetPos.x - bulletSpawn.x, targetPos.y - bulletSpawn.y };
        Vector2 normalizedDir = MathUtils::Normalize(dir);
        // Fallback to upward direction if normalization failed
        if (normalizedDir.x == 0.0f && normalizedDir.y == 0.0f) {
            normalizedDir = { 0, -1 };
        }
        SpawnBullet(bullets, bulletSpawn, normalizedDir, player.damage);
        shootTimer = player.attackRate;
    }
}


void HandlePlayerStats(Player& player) {
    // Placeholder for modular stat effects or regeneration, etc.
}
