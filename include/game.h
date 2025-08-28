#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include <string>
#include "Player.h"

class Game {
public:
    Game();
    ~Game();
    void Run();

private:
    void Setup();
    void Update();
    void Draw();
    void Cleanup();

    int screenWidth;
    int screenHeight;
    int targetFPS;
    std::string windowTitle;
    bool running;
    Player player;
};

#endif // GAME_H
