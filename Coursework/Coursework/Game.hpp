#ifndef COURSEWORK_GAME
#define COURSEWORK_GAME

#include "raylib.h"

#include "UIManager.hpp"

namespace Coursework {

    class Game {
    private:
        Coursework::UIManager uiManager;
    
    public:
        void run();
    };

}
#endif