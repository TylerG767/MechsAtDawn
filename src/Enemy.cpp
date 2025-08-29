#include "Enemy.h"
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include "Bullet.h"
#include "ScalingSystem.h"
#include "MathUtils.h" // for vector operations

void SpawnEnemy(std::vector<Enemy>& enemies, int screenWidth, int screenHeight, Vector2 playerPos, float minSpawnRadius, float speed, const ScalingParams& scaling) {
    Enemy e;
    e.size = {48, 48};
    // Find a spawn position outside minSpawnRadius from player
    for (int tries = 0; tries < 32; ++tries) {
        int edge = rand() % 4; // 0=top, 1=bottom, 2=left, 3=right
        switch(edge) {
            case 0: // top
                e.position = { (float)(rand() % (screenWidth - (int)e.size.x)), -e.size.y };
                break;
            case 1: // bottom
                e.position = { (float)(rand() % (screenWidth - (int)e.size.x)), (float)screenHeight };
                break;
            case 2: // left
                e.position = { -e.size.x, (float)(rand() % (screenHeight - (int)e.size.y)) };
                break;
            case 3: // right
                e.position = { (float)screenWidth, (float)(rand() % (screenHeight - (int)e.size.y)) };
                break;
        }
        Vector2 toPlayer = { playerPos.x - e.position.x, playerPos.y - e.position.y };
        float len = MathUtils::Distance(e.position, playerPos);
        if (len > minSpawnRadius) break;
    }
    e.enemyType = rand() % 2; // 0 or 1
    e.speed = (e.enemyType == 0) ? speed : speed * 1.2f;
    e.health = (e.enemyType == 0) ? scaling.baseHealth : scaling.baseHealth + 1;
    e.xpValue = (e.enemyType == 0) ? scaling.baseXP : scaling.baseXP + 5;
    float angleOffset = ((rand() % 21) - 10) * 0.05f; // random angle between -0.5 and 0.5 radians
    e.pathOffsetAngle = angleOffset;
    enemies.push_back(e);
}

void UpdateEnemies(std::vector<Enemy>& enemies, float screenWidth, float screenHeight, Vector2 playerPos) {
    for (auto& e : enemies) {
        Vector2 toPlayer = { playerPos.x - e.position.x, playerPos.y - e.position.y };
        Vector2 normalizedToPlayer = MathUtils::Normalize(toPlayer);
        float cosA = cosf(e.pathOffsetAngle);
        float sinA = sinf(e.pathOffsetAngle);
        float dirX = normalizedToPlayer.x * cosA - normalizedToPlayer.y * sinA;
        float dirY = normalizedToPlayer.x * sinA + normalizedToPlayer.y * cosA;
        float actualSpeed = e.speed * 0.6f;
        e.position.x += dirX * actualSpeed;
        e.position.y += dirY * actualSpeed;
    }
    // Remove dead or offscreen enemies
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [screenWidth,screenHeight](const Enemy& e){
        return (e.health <= 0 || e.position.x < -e.size.x*2 || e.position.x > screenWidth+e.size.x*2 || e.position.y < -e.size.y*2 || e.position.y > screenHeight+e.size.y*2);
    }), enemies.end());
}

void DrawEnemies(const std::vector<Enemy>& enemies, Texture2D enemyTexture) {
    int frameWidth = enemyTexture.width / 2;
    int frameHeight = enemyTexture.height;
    for (const auto& e : enemies) {
        Rectangle srcRect = { (float)(e.enemyType * frameWidth), 0, (float)frameWidth, (float)frameHeight };
        Rectangle destRect = { e.position.x, e.position.y, e.size.x, e.size.y };
        DrawTexturePro(enemyTexture, srcRect, destRect, {0,0}, 0.0f, WHITE);
    }
}
