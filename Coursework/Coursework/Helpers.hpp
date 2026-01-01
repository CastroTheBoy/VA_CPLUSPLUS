#pragma once

#include <cmath>

#include "raylib.h"

namespace Coursework {

    // General utility functions or mandatory globals

    static constexpr int DEFAULT_SCREEN_WIDTH = 1920;
    static constexpr int DEFAULT_SCREEN_HEIGHT = 1080;

    // Put the static methods inside a class to identify them easier in other files
    static class Helpers {
    public:

        
        static Color changeColorDarkness(Color color, float darkenValue) {
            return {
                static_cast<unsigned char>((static_cast<int>(color.r) * darkenValue)),
                static_cast<unsigned char>((static_cast<int>(color.g) * darkenValue)),
                static_cast<unsigned char>((static_cast<int>(color.b) * darkenValue)),
                color.a };
        }

        static float screenWidthAdjustmentCoefficient(float width) {
            return round_to(width / DEFAULT_SCREEN_WIDTH, 0.01);
        }

        static float screenHeightAdjustmentCoefficient(float height) {
            return round_to(height / DEFAULT_SCREEN_HEIGHT, 0.01);
        }

        static Rectangle resolutionAdjustedRectangle(Rectangle rec) {
            return {
                rec.x * screenWidthAdjustmentCoefficient(GetScreenWidth()),
                rec.y * screenHeightAdjustmentCoefficient(GetScreenHeight()),
                //rec.width * screenWidthAdjustmentCoefficient(GetScreenWidth()),
                //rec.height * screenHeightAdjustmentCoefficient(GetScreenHeight())
                rec.width,
                rec.height
            };
        }

        // Source - https://stackoverflow.com/a/14369745
        // Posted by paddy, modified by community. See post 'Timeline' for change history
        // Retrieved 2025-12-30, License - CC BY-SA 4.0

        static float round_to(float value, float precision = 1)
        {
            return std::round(value / precision) * precision;
        }

        static Rectangle recGetWorldToScreen2D(Rectangle* rec, Camera2D camera) {
            Vector2 temp = GetWorldToScreen2D({ rec->x, rec->y }, camera);
            return { temp.x, temp.y, rec->width, rec->height };
        }

    };

    

}