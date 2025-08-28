#include "Bullet.h"
#include <vector>
#include <algorithm>

void SpawnBullet(std::vector<Bullet>& bullets, const Vector2& spawnPos, const Vector2& direction, float damage) {
    Bullet b;
    b.position = spawnPos;
    b.velocity = {direction.x * 8.0f, direction.y * 8.0f};
    b.width = 6;
    b.height = 16;
    b.damage = damage;
    b.active = true;
    bullets.push_back(b);
}
// For backward compatibility (vertical shot)
void SpawnBullet(std::vector<Bullet>& bullets, const Vector2& spawnPos, float damage) {
    SpawnBullet(bullets, spawnPos, {0, -1}, damage);
}

void UpdateBullets(std::vector<Bullet>& bullets, float screenHeight) {
    for (auto& b : bullets) {
        if (!b.active) continue;
        b.position.x += b.velocity.x;
        b.position.y += b.velocity.y;
        if (b.position.y + b.height < 0) b.active = false;
    }
    // Remove inactive bullets
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](const Bullet& b){ return !b.active; }), bullets.end());
}

void DrawBullets(const std::vector<Bullet>& bullets) {
    for (const auto& b : bullets) {
        if (!b.active) continue;
        DrawRectangle(static_cast<int>(b.position.x), static_cast<int>(b.position.y), (int)b.width, (int)b.height, RED);
    }
}
