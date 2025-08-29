#include "Player.h"

#define PLAYER_START_X 400
#define PLAYER_START_Y 300
#define PLAYER_SPEED 4.0f
#define PLAYER_SIZE_X 48
#define PLAYER_SIZE_Y 48
#define PLAYER_HEALTH 100

void InitPlayer(Player& player) {
    player.position = { PLAYER_START_X, PLAYER_START_Y };
    player.speed = PLAYER_SPEED;
    player.size = { PLAYER_SIZE_X, PLAYER_SIZE_Y };
    player.health = PLAYER_HEALTH;
    player.damage = 1.0f;
    player.attackRate = 1.0f;
    player.texture = LoadTexture("../assets/models/Player_1.png");
}

// Removed UpdatePlayer. Player input and clamping are now handled by HandlePlayerInput in PlayerSystem.cpp.

void DrawPlayer(const Player& player) {
    DrawTextureEx(player.texture, player.position, 0.0f, player.size.x / (float)player.texture.width, WHITE);
}

void UnloadPlayer(Player& player) {
    UnloadTexture(player.texture);
}
