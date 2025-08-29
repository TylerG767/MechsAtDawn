#ifndef RENDERUTILS_H
#define RENDERUTILS_H

#include "raylib.h"
#include "GameConfig.h"

// Centralized rendering utilities to avoid code duplication
namespace RenderUtils {
    // Get default font (cached to avoid repeated calls)
    inline Font GetDefaultFont() {
        static Font defaultFont = GetFontDefault();
        return defaultFont;
    }
    
    // Helper to calculate center position for XP orb spawning
    inline Vector2 GetEntityCenter(Vector2 position, Vector2 size) {
        return { position.x + size.x / 2, position.y + size.y / 2 };
    }
    
    // Scale factor based on current screen size vs default
    inline float GetUIScale() {
        float scaleX = (float)GameConfig::SCREEN_WIDTH / GameConfig::DEFAULT_SCREEN_WIDTH;
        float scaleY = (float)GameConfig::SCREEN_HEIGHT / GameConfig::DEFAULT_SCREEN_HEIGHT;
        return (scaleX + scaleY) * 0.5f; // Average of both scales
    }
    
    // Get scaled font size
    inline float GetScaledFontSize(float baseFontSize) {
        return baseFontSize * GetUIScale();
    }
    
    // Get position relative to screen size (percentages: 0.0-1.0)
    inline Vector2 GetRelativePosition(float xPercent, float yPercent) {
        return { GameConfig::SCREEN_WIDTH * xPercent, GameConfig::SCREEN_HEIGHT * yPercent };
    }
    
    // Get position with offset from edges
    inline Vector2 GetEdgePosition(float leftOffset, float topOffset, float rightOffset = -1, float bottomOffset = -1) {
        float x = (rightOffset >= 0) ? GameConfig::SCREEN_WIDTH - rightOffset : leftOffset;
        float y = (bottomOffset >= 0) ? GameConfig::SCREEN_HEIGHT - bottomOffset : topOffset;
        return { x, y };
    }
}

#endif // RENDERUTILS_H
