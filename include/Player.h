#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

struct Player {
    Vector2 position;
    Vector2 size;
    float speed;
    int health;
    float damage;
    float attackRate;
    Texture2D texture;
    int xp;
    int level;
    int xpToLevel;
    bool levelUpState;
};

void InitPlayer(Player& player);
void UpdatePlayer(Player& player);
void DrawPlayer(const Player& player);
void UnloadPlayer(Player& player);



#endif // PLAYER_H
