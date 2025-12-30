#ifndef COURSEWORK_UIMANAGER
#define COURSEWORK_UIMANAGER

#include <unordered_map>
#include <functional>
#include <utility>
#include <string>

#include "raylib.h"

#include "MenuScreen.hpp"
#include "EventHandler.hpp"

namespace Coursework {

    enum GameState { INITIAL, ACTIVE, PAUSED, EXIT_REQUEST };

    class UIManager {
    private:
        // Eventually change this to a generic 'screen' and just call draw on each
        // Bool for each screen to indicate if it should be drawn
        std::unordered_map<std::string, std::pair<MenuScreen*, bool>> uiScreens;

        EventHandler* uiEvents;

        static void setup(UIManager* uiManager);

        void setScreenAsOnlyActive(std::string);

        void resize();

    public:
        GameState gameState;

        void draw();

        void changeScreenToSettings();
        void changeScreenToMainMenu();
        void setGameStateExitRequest();
        void setFullScreen();
        // Because of my decision to have parameterless callbacks have to do this
        // It's not the worst thing, but I know
        void setResolutionTo_1920_1080();
        void setResolutionTo_800_600();

        void dummy() {};

        UIManager();

        ~UIManager();

    };

}
#endif