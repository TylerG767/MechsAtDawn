#include "PlayerSystem.h"
#include <raylib.h>

void HandlePlayerInput(Player& player, float delta) {
    if (IsKeyDown(KEY_W)) player.position.y -= player.speed;
    if (IsKeyDown(KEY_S)) player.position.y += player.speed;
    if (IsKeyDown(KEY_A)) player.position.x -= player.speed;
    if (IsKeyDown(KEY_D)) player.position.x += player.speed;
    // Clamp player inside window (assuming 800x600)
    if (player.position.x < 0) player.position.x = 0;
    if (player.position.y < 0) player.position.y = 0;
    if (player.position.x > 800 - player.size.x) player.position.x = 800 - player.size.x;
    if (player.position.y > 600 - player.size.y) player.position.y = 600 - player.size.y;
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
        float len = sqrtf(dir.x*dir.x + dir.y*dir.y);
        if (len > 0.01f) {
            dir.x /= len;
            dir.y /= len;
        } else {
            dir.x = 0;
            dir.y = -1;
        }
        SpawnBullet(bullets, bulletSpawn, dir, player.damage);
        shootTimer = player.attackRate;
    }
}


void HandlePlayerStats(Player& player) {
    // Placeholder for modular stat effects or regeneration, etc.
}
