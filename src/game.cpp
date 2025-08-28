#include "game.h"
#include <string>
Game::Game() {
    screenWidth = 800;
    screenHeight = 600;
    targetFPS = 60;
    windowTitle = "Mechs At Dawn";
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
    UpdatePlayer(player);
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    Font font = GetFontDefault();
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
