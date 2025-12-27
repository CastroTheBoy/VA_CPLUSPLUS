#include <forward_list>

#include "raylib.h"

#include "Button.hpp"
#include "MenuScreen.hpp"

// Since there shouldn't be countless buttons it's fine to iterate through all objects and check instead of complex stuff like position grouping
void Coursework::MenuScreen::checkButtonClick() {
	for (auto i : buttons)
		if (CheckCollisionPointRec(GetMousePosition(), i->rectangle)) {
			// Cursor overlaps and left mouse button is clicked
			if (IsMouseButtonDown(0))
				// Only call onClick the first time
				if (!i->isClicked)
					i->onClick();
				else
					continue;
			// Cursor overalps, button has isClicked flag, but mouse left is no longer down
			else if (i->isClicked)
				i->onRelease(true);
		}
		else {
			// Cursor does not overlap, mouse button is down and button has isClicked flag
			// Technically should only happen if You click the button and move the cursor off while still holding mouse left down
			if (IsMouseButtonDown(0) && i->isClicked)
				i->onRelease(false);
		}
}

// This will have to somehow be adjusted to work nicely with cameras
// Maybe pass a Camera2D as param and call GetWorldToScreen2D
void Coursework::MenuScreen::drawButtons() {
	for (auto& i : buttons) {
		// Button main body
		Rectangle temp = recGetWorldToScreen2D(&(i->rectangle));
		DrawRectangleRec(temp, i->color);

		// Button border, will have a hardcoded size and be based on inverse of current color
		DrawRectangleLinesEx(temp, 2, i->colorAlt);

		// Button text - think of resizing issues for all of this later
		// Draws text in the middle of button rectangle, hardcoded for font size 20, make sure text length doesn't exceed button length!
		int textWidth = MeasureText(i->text.c_str(), 20);
		DrawText(i->text.c_str(), temp.x + (temp.width / 2)  - (textWidth / 2), temp.y + (temp.height / 2) - 10, 20, BLACK);
	}
}

// Do I need this?
Rectangle Coursework::MenuScreen::recGetWorldToScreen2D(Rectangle *rec) {
	Vector2 temp = GetWorldToScreen2D({ rec->x, rec->y }, this->camera);
	return { temp.x, temp.y, rec->width, rec->height };
}

Coursework::MenuScreen::MenuScreen(Color color) : Background(color)
{
	this->camera.offset.x = 0;
	this->camera.offset.y = 0;
	this->camera.target.x = 0;
	this->camera.target.y = 0;
	this->camera.rotation = 0;
	this->camera.zoom = 1;
};

Coursework::MenuScreen::MenuScreen(Color color, Camera2D camera) : Background(color), camera(camera) {};
		
// I can't imagine a scenario where I would remove a button
// So let UI layout be static since decleration (i.e. no removeButtion())
void Coursework::MenuScreen::addButton(Coursework::Button *button) {
	buttons.push_front(button);
}
	
// Call this after BeginDrawing to draw the screen and it's contents
// Screen will always draw relative to screen coordinates and not world, so use only for UI type drawables
void Coursework::MenuScreen::drawScreen() {
	checkButtonClick();

	BeginMode2D(this->camera);

	// Draw menu background, ideally this has an alpha <255, especially if it's a pause menu screen
	DrawRectangleRec({0, 0, static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight())}, this->Background);

	drawButtons();

	EndMode2D();
}

Coursework::MenuScreen::~MenuScreen()
{
	for (auto& i : buttons)
		delete i;
};