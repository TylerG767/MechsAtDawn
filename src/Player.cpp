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
    player.attackRate = 0.2f;
    player.texture = LoadTexture("../assets/models/Player_1.png");
}

void UpdatePlayer(Player& player) {
    if (IsKeyDown(KEY_W)) player.position.y -= player.speed;
    if (IsKeyDown(KEY_S)) player.position.y += player.speed;
    if (IsKeyDown(KEY_A)) player.position.x -= player.speed;
    if (IsKeyDown(KEY_D)) player.position.x += player.speed;

    // Clamp player inside window
    if (player.position.x < 0) player.position.x = 0;
    if (player.position.y < 0) player.position.y = 0;
    if (player.position.x > 800 - player.size.x) player.position.x = 800 - player.size.x;
    if (player.position.y > 600 - player.size.y) player.position.y = 600 - player.size.y;
}

void DrawPlayer(const Player& player) {
    DrawTextureEx(player.texture, player.position, 0.0f, player.size.x / (float)player.texture.width, WHITE);
}

void UnloadPlayer(Player& player) {
    UnloadTexture(player.texture);
}
