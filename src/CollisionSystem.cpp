#include "CollisionSystem.h"
#include <raylib.h>
#include "XPOrb.h"
#include "MathUtils.h" // for Rectangle creation helper
#include "RenderUtils.h" // for entity center calculations
void HandleCollisions(Player& player, std::vector<Enemy>& enemies, std::vector<Bullet>& bullets, int& score, std::vector<XPOrb>& xpOrbs) {
    // Bullet-enemy collision
    for (auto& bullet : bullets) {
        if (!bullet.active) continue;
        Rectangle bulletRect = MathUtils::CreateRect(bullet.position, {bullet.width, bullet.height});
        for (auto& enemy : enemies) {
            Rectangle enemyRect = MathUtils::CreateRect(enemy.position, enemy.size);
            if (enemy.health > 0 && CheckCollisionRecs(bulletRect, enemyRect)) {
                enemy.health -= static_cast<int>(bullet.damage);
                bullet.active = false;
                if (enemy.health <= 0) {
                    score += 100;
                    SpawnXPOrb(xpOrbs, RenderUtils::GetEntityCenter(enemy.position, enemy.size), enemy.xpValue);
                }
            }
        }
    }
    // Player-enemy collision
    Rectangle playerRect = MathUtils::CreateRect(player.position, player.size);
    for (auto& enemy : enemies) {
        Rectangle enemyRect = MathUtils::CreateRect(enemy.position, enemy.size);
        if (enemy.health > 0 && CheckCollisionRecs(playerRect, enemyRect)) {
            enemy.health = 0;
            player.health -= 1;
            SpawnXPOrb(xpOrbs, RenderUtils::GetEntityCenter(enemy.position, enemy.size), enemy.xpValue);
        }
    }
}
