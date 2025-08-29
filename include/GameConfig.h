#ifndef GAMECONFIG_H
#define GAMECONFIG_H

// Centralized game configuration
namespace GameConfig {
    // Adjustable screen dimensions (can be modified at runtime)
    extern int SCREEN_WIDTH;
    extern int SCREEN_HEIGHT;
    
    // Fixed configuration constants
    constexpr int TARGET_FPS = 60;
    constexpr const char* WINDOW_TITLE = "Mechs At Dawn";
    
    // Default screen dimensions
    constexpr int DEFAULT_SCREEN_WIDTH = 800;
    constexpr int DEFAULT_SCREEN_HEIGHT = 600;
    
    // Initialize screen dimensions (call once at startup)
    void InitializeScreenSize(int width = DEFAULT_SCREEN_WIDTH, int height = DEFAULT_SCREEN_HEIGHT);
    
    // Update screen dimensions (for window resizing)
    void UpdateScreenSize(int width, int height);
}

#endif // GAMECONFIG_H
