#include <unordered_map>
#include <string>
#include <functional>
#include <utility>

#include "raylib.h"

#include "MenuScreen.hpp"
#include "UIManager.hpp"
#include "EventHandler.hpp"

using namespace Coursework;

void UIManager::setup (UIManager* uiManager) {

    // ----------------------- EVENTS -----------------------
    uiManager->uiEvents = new EventHandler();

    // Link events
    uiManager->uiEvents->addCallback(MAIN_MENU_START_ON_RELEASE, std::bind(&UIManager::dummy, uiManager));
    uiManager->uiEvents->addCallback(MAIN_MENU_SETTING_ON_RELEASE, std::bind(&UIManager::changeScreenToSettings, uiManager));
    uiManager->uiEvents->addCallback(MAIN_MENU_EXIT_ON_RELEASE, std::bind(&UIManager::setGameStateExitRequest, uiManager));
    uiManager->uiEvents->addCallback(SETTING_RETURN_ON_RELEASE, std::bind(&UIManager::changeScreenToMainMenu, uiManager));

    // --------------------------------------------------------

    float buttonWidth = 200;
    float buttonHeight = 50;

    float width = GetScreenWidth();
    float height = GetScreenHeight();

    // For now hardcode the button positions, later set them based on window size 
        
    // ----------------------- MAIN MENU -----------------------
    // Start game
    Button* buttonMainStart = new Button(
        width / 2 - buttonWidth / 2,
        50,
        buttonWidth,
        buttonHeight,
        { 198, 202, 83, 255 },
        { 123, 114, 99, 255 },
        "Start Game",
        std::make_pair(MAIN_MENU_START_ON_RELEASE, std::bind(&EventHandler::fireEvent, uiManager->uiEvents, std::placeholders::_1)));
    
    // Settings
    Button* buttonMainSettings = new Button(
        width / 2 - buttonWidth / 2,
        250,
        buttonWidth,
        buttonHeight,
        { 198, 202, 83, 255 },
        { 123, 114, 99, 255 },
        "Settings",
        std::make_pair(MAIN_MENU_SETTING_ON_RELEASE, std::bind(&EventHandler::fireEvent, uiManager->uiEvents, std::placeholders::_1)));

    // Exit
    Button* buttonMainExit = new Button(
        width / 2 - buttonWidth / 2,
        height - buttonHeight - 100,
        buttonWidth,
        buttonHeight,
        { 198, 202, 83, 255 },
        { 123, 114, 99, 255 },
        "Exit",
        std::make_pair(MAIN_MENU_EXIT_ON_RELEASE, std::bind(&EventHandler::fireEvent, uiManager->uiEvents, std::placeholders::_1)));

    // Screen setup and bindings
    MenuScreen *screenMainMenu = new MenuScreen({ 0, 0, 0, 125 });
    screenMainMenu->addButton(buttonMainStart);
    screenMainMenu->addButton(buttonMainExit);
    screenMainMenu->addButton(buttonMainSettings);
    
    uiManager->uiScreens["MAIN_MENU"] = std::make_pair(screenMainMenu, false);
    // --------------------------------------------------------

    // ----------------------- SETTINGS -----------------------
    // Return
    Button *buttonAlt = new Button(
        width / 2 - buttonWidth / 2,
        height - buttonHeight - 100,
        buttonWidth,
        buttonHeight,
        { 198, 202, 83, 255 },
        { 123, 114, 99, 255 },
        "Return",
        std::make_pair(SETTING_RETURN_ON_RELEASE, std::bind(&EventHandler::fireEvent, uiManager->uiEvents, std::placeholders::_1)));

    // Screen setup and bindings
    MenuScreen *screenAlt = new MenuScreen({ 0,0,0,200 });
    screenAlt->addButton(buttonAlt);

    uiManager->uiScreens["SETTINGS"] = std::make_pair(screenAlt, false);
    // --------------------------------------------------------
    
    // Set draw states for screens
    uiManager->uiScreens["MAIN_MENU"].second = true;
    
}

// Rewrite to be able to set specific order
void UIManager::draw() {
    for (auto& i : uiScreens) {
        if (i.second.second)
            i.second.first->drawScreen();
    }
}

void UIManager::changeScreenToSettings() {
    setScreenAsOnlyActive("SETTINGS");
}

void UIManager::changeScreenToMainMenu() {
    setScreenAsOnlyActive("MAIN_MENU");
}

void UIManager::setScreenAsOnlyActive(std::string screen) {
    for (auto& i : uiScreens)
        i.second.second = i.first == screen;
}

void UIManager::setGameStateExitRequest() {
    gameState = GameState::EXIT_REQUEST;
}

UIManager::UIManager() {
    setup(this);
}

UIManager::~UIManager() {
    delete uiEvents;
    for (auto i : uiScreens)
        delete i.second.first;
}