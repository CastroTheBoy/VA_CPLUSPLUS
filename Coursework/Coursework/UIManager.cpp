#include <unordered_map>
#include <string>
#include <functional>
#include <utility>

#include "raylib.h"

#include "MenuScreen.hpp"
#include "UIManager.hpp"
#include "EventHandler.hpp"
#include "CheckBox.hpp"
#include "Button.hpp"
#include "IDrawable.hpp"
#include "DrawableList.hpp"

using namespace Coursework;

void UIManager::setup (UIManager* uiManager) {

    // ----------------------- EVENTS -----------------------
    uiManager->uiEvents = new EventHandler();

    // Link events
    uiManager->uiEvents->addCallback(MAIN_MENU_START_ON_RELEASE, std::bind(&UIManager::dummy, uiManager));
    uiManager->uiEvents->addCallback(MAIN_MENU_SETTING_ON_RELEASE, std::bind(&UIManager::changeScreenToSettings, uiManager));
    uiManager->uiEvents->addCallback(MAIN_MENU_EXIT_ON_RELEASE, std::bind(&UIManager::setGameStateExitRequest, uiManager));
    uiManager->uiEvents->addCallback(SETTING_RETURN_ON_RELEASE, std::bind(&UIManager::changeScreenToMainMenu, uiManager));
    uiManager->uiEvents->addCallback(SETTING_FULLSCREEN_ON_RELEASE, std::bind(&UIManager::setFullScreen, uiManager));
    uiManager->uiEvents->addCallback(SCREEN_RESIZE_1920_1080, std::bind(&UIManager::setResolutionTo_1920_1080, uiManager));
    uiManager->uiEvents->addCallback(SCREEN_RESIZE_800_600, std::bind(&UIManager::setResolutionTo_800_600, uiManager));

    // --------------------------------------------------------

    float buttonWidth = 200;
    float buttonHeight = 50;

    float width = GetScreenWidth();
    float height = GetScreenHeight();

    // ----------------------- MAIN MENU -----------------------
    // Start game
    Button* buttonMainStart = new Button(
        1,
        1,
        buttonWidth,
        buttonHeight,
        { 198, 202, 83, 255 },
        { 123, 114, 99, 255 },
        "Start Game",
        std::make_pair(MAIN_MENU_START_ON_RELEASE, std::bind(&EventHandler::fireEvent, uiManager->uiEvents, std::placeholders::_1)));
    
    // Settings
    Button* buttonMainSettings = new Button(
        1,
        1,
        buttonWidth,
        buttonHeight,
        { 198, 202, 83, 255 },
        { 123, 114, 99, 255 },
        "Settings",
        std::make_pair(MAIN_MENU_SETTING_ON_RELEASE, std::bind(&EventHandler::fireEvent, uiManager->uiEvents, std::placeholders::_1)));

    // Exit
    Button* buttonMainExit = new Button(
        1,
        1,
        buttonWidth,
        buttonHeight,
        { 198, 202, 83, 255 },
        { 123, 114, 99, 255 },
        "Exit",
        std::make_pair(MAIN_MENU_EXIT_ON_RELEASE, std::bind(&EventHandler::fireEvent, uiManager->uiEvents, std::placeholders::_1)));

    DrawableList* mainMenuDrawables = new DrawableList(0.1, 0.1, 0.5, JUSTIFIED);

    mainMenuDrawables->addDrawable(buttonMainStart);
    mainMenuDrawables->addDrawable(buttonMainSettings);
    mainMenuDrawables->addDrawable(buttonMainExit);

    // Screen setup and bindings
    MenuScreen *screenMainMenu = new MenuScreen({ 0, 0, 0, 125 });
    screenMainMenu->addDrawableList(mainMenuDrawables);
    
    uiManager->uiScreens["MAIN_MENU"] = std::make_pair(screenMainMenu, false);
    // --------------------------------------------------------

    // ----------------------- SETTINGS -----------------------
    // Return
    Button *btnSettingsReturn = new Button(
        1,
        1,
        buttonWidth,
        buttonHeight,
        { 198, 202, 83, 255 },
        { 123, 114, 99, 255 },
        "Return",
        std::make_pair(SETTING_RETURN_ON_RELEASE, std::bind(&EventHandler::fireEvent, uiManager->uiEvents, std::placeholders::_1)));

    DrawableList* settingsReturnButton = new DrawableList(0.1, 0.8, 0.7, JUSTIFIED);

    settingsReturnButton->addDrawable(btnSettingsReturn);

    Checkbox* cbxSettingsFullscreen = new Checkbox(
        1,
        1,
        buttonWidth,
        buttonHeight,
        { 198, 202, 83, 255 },
        { 123, 114, 99, 255 },
        "Fullscreen",
        std::make_pair(SETTING_FULLSCREEN_ON_RELEASE, std::bind(&EventHandler::fireEvent, uiManager->uiEvents, std::placeholders::_1)));

    cbxSettingsFullscreen->isChecked = IsWindowFullscreen();

    Button* btnSettingsRes_1920_1080 = new Button(
        1,
        1,
        buttonWidth,
        buttonHeight,
        { 198, 202, 83, 255 },
        { 123, 114, 99, 255 },
        "1920 X 1080",
        std::make_pair(SCREEN_RESIZE_1920_1080, std::bind(&EventHandler::fireEvent, uiManager->uiEvents, std::placeholders::_1)));

    Button* btnSettingsRes_800_600 = new Button(
        1,
        1,
        buttonWidth,
        buttonHeight,
        { 198, 202, 83, 255 },
        { 123, 114, 99, 255 },
        "800 X 600",
        std::make_pair(SCREEN_RESIZE_800_600, std::bind(&EventHandler::fireEvent, uiManager->uiEvents, std::placeholders::_1)));
    
    DrawableList* settingsConfigurationButtons = new DrawableList(0.1, 0.1, 0.2, JUSTIFIED);
    settingsConfigurationButtons->addDrawable(cbxSettingsFullscreen);
    settingsConfigurationButtons->addDrawable(btnSettingsRes_1920_1080);
    settingsConfigurationButtons->addDrawable(btnSettingsRes_800_600);

    // Screen setup and bindings
    MenuScreen *screenAlt = new MenuScreen({ 0,0,0,200 });
    screenAlt->addDrawableList(settingsReturnButton);
    screenAlt->addDrawableList(settingsConfigurationButtons);

    uiManager->uiScreens["SETTINGS"] = std::make_pair(screenAlt, false);
    // --------------------------------------------------------
    
    // Set draw states for screens
    uiManager->uiScreens["MAIN_MENU"].second = true;
    
}

// Will this screw me over if it's called in the middle of the draw cycle?
void UIManager::setResolutionTo_1920_1080() {
    SetWindowSize(1920, 1080);
    resize();
}

void UIManager::setResolutionTo_800_600() {
    SetWindowSize(800, 600);
    resize();
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

void UIManager::setFullScreen() {
    ToggleFullscreen();
    resize();
}

UIManager::UIManager() {
    setup(this);
}

UIManager::~UIManager() {
    delete uiEvents;
    for (auto i : uiScreens)
        delete i.second.first;
}

void UIManager::resize() {
    SetWindowPosition(
        GetMonitorWidth(GetCurrentMonitor()) / 2 - GetScreenWidth() / 2,
        GetMonitorHeight(GetCurrentMonitor()) / 2 - GetScreenHeight() / 2
    );
    
    for (auto& i : uiScreens) {
        i.second.first->resizeDrawables();
    }
}