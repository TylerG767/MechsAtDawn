#ifndef MATHUTILS_H
#define MATHUTILS_H

#include "raylib.h"
#include <cmath>

// Centralized math utilities to avoid code duplication
namespace MathUtils {
    // Normalize a 2D vector (returns normalized vector)
    inline Vector2 Normalize(Vector2 vec) {
        float len = sqrtf(vec.x * vec.x + vec.y * vec.y);
        if (len > 0.01f) {
            return { vec.x / len, vec.y / len };
        }
        return { 0.0f, 0.0f }; // Return zero vector if too small
    }
    
    // Calculate distance between two points
    inline float Distance(Vector2 a, Vector2 b) {
        float dx = b.x - a.x;
        float dy = b.y - a.y;
        return sqrtf(dx * dx + dy * dy);
    }
    
    // Calculate squared distance (faster when you don't need exact distance)
    inline float DistanceSquared(Vector2 a, Vector2 b) {
        float dx = b.x - a.x;
        float dy = b.y - a.y;
        return dx * dx + dy * dy;
    }
    
    // Create a Rectangle from position and size vectors
    inline Rectangle CreateRect(Vector2 position, Vector2 size) {
        return { position.x, position.y, size.x, size.y };
    }
}

#endif // MATHUTILS_H
