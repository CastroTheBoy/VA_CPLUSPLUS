#include "raylib.h"

#include "Game.hpp"
#include "Helpers.hpp"

using namespace Coursework;

void Game::run() {

    InitWindow(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, "Coursework");
    ToggleFullscreen();
    SetTargetFPS(60);

    int debugTextFontSize = 20;
    int debugTextPosY = 20;
    int debugTextPosX = 0;
    
    // Basically this needs to be initialized after InitWindow(), so have it exist in run() instead of being a member to Game
    UIManager uiManager;

    while (true)
    {
        int debugIncrement = 0;

        // Draw order is very important. Each screen in uiManager uses it's own camera so things are layered on top of each other.
        BeginDrawing();

        // Not for this project, but look into partial redrawing.
        ClearBackground(WHITE);
        
        uiManager.draw();
        
        // Add debug mode check for this
        DrawFPS(0, 0);
        DrawText(TextFormat("Screen width: %i", GetScreenWidth()), debugTextPosX, debugTextPosY + debugTextFontSize * debugIncrement++,debugTextFontSize, BLACK);
        DrawText(TextFormat("Screen height: %i", GetScreenHeight()), debugTextPosX, debugTextPosY + debugTextFontSize * debugIncrement++, debugTextFontSize, BLACK);

        const char* temp = TextFormat("Mouse X: %i", GetMouseX());
        DrawText(temp, GetScreenWidth() - MeasureText(temp, 20), debugTextPosY + debugTextFontSize * debugIncrement++, debugTextFontSize, BLACK);
        temp = TextFormat("Mosue Y: %i", GetMouseY());
        DrawText(temp, GetScreenWidth() - MeasureText(temp, 20), debugTextPosY + debugTextFontSize * debugIncrement++, debugTextFontSize, BLACK);

        EndDrawing();

        // Custom exit
        if (uiManager.gameState == GameState::EXIT_REQUEST || WindowShouldClose()) {
            CloseWindow();
            // This should be the final step in the game. Do any unloading, saving etc. before.
            return;
        }
    }
}