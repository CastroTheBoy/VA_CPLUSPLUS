#include <unordered_map>
#include <string>
#include <functional>
#include <utility>

#include "raylib.h"

#include "MenuScreen.hpp"
#include "UIManager.hpp"

void Coursework::UIManager::setup (UIManager* uiManager) {

    float buttonWidth = 200;
    float buttonHeight = 50;

    float width = GetScreenWidth();
    float height = GetScreenHeight();

    // For now hardcode the button positions, later set them based on window size 
        
    // ----------------------- MAIN MENU -----------------------
    // Start game
    Coursework::Button* buttonMainStart = new Coursework::Button(
        width / 2 - buttonWidth / 2,
        50,
        buttonWidth,
        buttonHeight,
        { 198, 202, 83, 255 },
        { 123, 114, 99, 255 },
        "Start Game");
    buttonMainStart->addOnReleaseCallback(std::bind(&UIManager::dummy, uiManager));
    
    // Settings
    Coursework::Button* buttonMainSettings = new Coursework::Button(
        width / 2 - buttonWidth / 2,
        250,
        buttonWidth,
        buttonHeight,
        { 198, 202, 83, 255 },
        { 123, 114, 99, 255 },
        "Settings");
    buttonMainSettings->addOnReleaseCallback(std::bind(&UIManager::changeScreenToSettings, uiManager));

    // Exit
    Coursework::Button* buttonMainExit = new Coursework::Button(
        width / 2 - buttonWidth / 2,
        height - buttonHeight - 100,
        buttonWidth,
        buttonHeight,
        { 198, 202, 83, 255 },
        { 123, 114, 99, 255 },
        "Exit");
    buttonMainExit->addOnReleaseCallback(std::bind(&UIManager::setGameStateExitRequest, uiManager));

    // Screen setup and bindings
    Coursework::MenuScreen *screenMainMenu = new Coursework::MenuScreen({ 0, 0, 0, 125 });
    screenMainMenu->addButton(buttonMainStart);
    screenMainMenu->addButton(buttonMainExit);
    screenMainMenu->addButton(buttonMainSettings);
    
    uiManager->uiScreens["MAIN_MENU"] = std::make_pair(screenMainMenu, false);
    // --------------------------------------------------------

    // ----------------------- SETTINGS -----------------------
    // Return
    Coursework::Button *buttonAlt = new Coursework::Button(
        width / 2 - buttonWidth / 2,
        height - buttonHeight - 100,
        buttonWidth,
        buttonHeight,
        { 198, 202, 83, 255 },
        { 123, 114, 99, 255 },
        "Return");
    buttonAlt->addOnReleaseCallback(std::bind(&UIManager::changeScreenToMainMenu, uiManager));

    // Screen setup and bindings
    Coursework::MenuScreen *screenAlt = new Coursework::MenuScreen({ 0,0,0,200 });
    screenAlt->addButton(buttonAlt);

    uiManager->uiScreens["SETTINGS"] = std::make_pair(screenAlt, false);
    // --------------------------------------------------------
    
    // Set draw states for screens
    uiManager->uiScreens["MAIN_MENU"].second = true;
    
}

// Rewrite to be able to set specific order
void Coursework::UIManager::draw() {
    for (auto& i : uiScreens) {
        if (i.second.second)
            i.second.first->drawScreen();
    }
}

void Coursework::UIManager::changeScreenToSettings() {
    setScreenAsOnlyActive("SETTINGS");
}

void Coursework::UIManager::changeScreenToMainMenu() {
    setScreenAsOnlyActive("MAIN_MENU");
}

void Coursework::UIManager::setScreenAsOnlyActive(std::string screen) {
    for (auto& i : uiScreens)
        i.second.second = i.first == screen;
}

void Coursework::UIManager::setGameStateExitRequest() {
    gameState = Coursework::GameState::EXIT_REQUEST;
}

Coursework::UIManager::UIManager() {
    setup(this);
}