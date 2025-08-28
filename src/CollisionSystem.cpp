#include "CollisionSystem.h"
#include <raylib.h>

#include "XPOrb.h"
void HandleCollisions(Player& player, std::vector<Enemy>& enemies, std::vector<Bullet>& bullets, int& score, std::vector<XPOrb>& xpOrbs) {
    // Bullet-enemy collision
    for (auto& bullet : bullets) {
        if (!bullet.active) continue;
        Rectangle bulletRect = { bullet.position.x, bullet.position.y, bullet.width, bullet.height };
        for (auto& enemy : enemies) {
            Rectangle enemyRect = { enemy.position.x, enemy.position.y, enemy.size.x, enemy.size.y };
            if (enemy.health > 0 && CheckCollisionRecs(bulletRect, enemyRect)) {
                enemy.health -= static_cast<int>(bullet.damage);
                bullet.active = false;
                if (enemy.health <= 0) {
                    score += 100;
                    SpawnXPOrb(xpOrbs, {enemy.position.x + enemy.size.x/2, enemy.position.y + enemy.size.y/2}, enemy.xpValue);
                }
            }
        }
    }
    // Player-enemy collision
    Rectangle playerRect = { player.position.x, player.position.y, player.size.x, player.size.y };
    for (auto& enemy : enemies) {
        Rectangle enemyRect = { enemy.position.x, enemy.position.y, enemy.size.x, enemy.size.y };
        if (enemy.health > 0 && CheckCollisionRecs(playerRect, enemyRect)) {
            enemy.health = 0;
            player.health -= 1;
            SpawnXPOrb(xpOrbs, {enemy.position.x + enemy.size.x/2, enemy.position.y + enemy.size.y/2}, enemy.xpValue);
        }
    }
}
