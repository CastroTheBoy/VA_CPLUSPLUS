#include "raylib.h"

#include "Game.hpp"

using namespace Coursework;

void Game::run() {

    InitWindow(800, 600, "Coursework");
    SetTargetFPS(60);

    int debugTextFontSize = 20;
    int debugTextPosY = 20;
    int debugTextPosX = 20;

    // Basically this needs to be initialized after InitWindow(), so have it exist in run instead of being a member to Game
    UIManager uiManager;

    while (true)
    {
        // Draw order is very important. Each screen in uiManager uses it's own camera so things are layered on top of each other.
        BeginDrawing();

        // Not for this project, but look into partial redrawing.
        ClearBackground(WHITE);
        // Add debug mode check for this
        DrawFPS(0, 0);

        uiManager.draw();

        EndDrawing();

        // Custom exit
        if (uiManager.gameState == GameState::EXIT_REQUEST || WindowShouldClose()) {
            CloseWindow();
            // This should be the final step in the game. Do any unloading, saving etc. before.
            return;
        }
    }
}