#include "game.h"
#include <string>
#include "PlayerSystem.h" // for HandlePlayerInput
#include "GameConfig.h" // for centralized configuration
#include "RenderUtils.h" // for rendering helpers

Game::Game() {
    // Use centralized configuration constants
    screenWidth = GameConfig::SCREEN_WIDTH;
    screenHeight = GameConfig::SCREEN_HEIGHT;
    targetFPS = GameConfig::TARGET_FPS;
    windowTitle = GameConfig::WINDOW_TITLE;
    running = true;
}

Game::~Game() {
    Cleanup();
}

void Game::Setup() {
    InitWindow(screenWidth, screenHeight, windowTitle.c_str());
    SetTargetFPS(targetFPS);
    InitPlayer(player);
}

void Game::Update() {
    if (WindowShouldClose()) running = false;
    // Use unified input handler (movement + clamping)
    HandlePlayerInput(player, GetFrameTime());
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    Font font = RenderUtils::GetDefaultFont();
    DrawTextEx(font, "Mechs At Dawn Prototype", { 180, 280 }, 32, 2, DARKGRAY);
    DrawPlayer(player);
    EndDrawing();
}


void Game::Cleanup() {
    UnloadPlayer(player);
    CloseWindow();
}

void Game::Run() {
    Setup();
    while (running) {
        Update();
        Draw();
    }
    Cleanup();
}
