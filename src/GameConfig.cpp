#include "GameConfig.h"

namespace GameConfig {
    // Define the adjustable screen dimensions
    int SCREEN_WIDTH = DEFAULT_SCREEN_WIDTH;
    int SCREEN_HEIGHT = DEFAULT_SCREEN_HEIGHT;
    
    void InitializeScreenSize(int width, int height) {
        SCREEN_WIDTH = width;
        SCREEN_HEIGHT = height;
    }
    
    void UpdateScreenSize(int width, int height) {
        SCREEN_WIDTH = width;
        SCREEN_HEIGHT = height;
    }
}
