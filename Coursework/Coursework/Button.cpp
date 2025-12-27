#include "raylib.h"
#include "Button.hpp"
#include <iostream>
using namespace Coursework;

Button::Button(int x, int y, int width, int height, Color colorStandard, Color colorHighlight, std::string const& text, CallbackTrigger callback) :
	color(colorStandard), colorAlt(colorHighlight), colorStandard(colorStandard), colorHighlight(colorHighlight), text(text), callbackTrigger(callback)
{
	rectangle = Rectangle(x, y, width, height);
}

Button::Button(int x, int y, int width, int height, Color colorStandard, Color colorHighlight, CallbackTrigger callback) :
	Button(x, y, width, height, colorStandard, colorHighlight, "", callback) {};

void Button::onClick() {
	isClicked = true;
	std::cout << text << " - onClick" << '\n';
	color = colorHighlight;
	colorAlt = colorStandard;
}

void Button::onRelease(bool fireCallbacks) {
	isClicked = false;
	// Again, just reference the base values
	std::cout << text << " - onRelease" << '\n';
	color = colorStandard;
	colorAlt = colorHighlight;
	if (fireCallbacks)
		callbackTrigger.second(callbackTrigger.first);
}

void Button::checkSelfClick() {
	if (CheckCollisionPointRec(GetMousePosition(), rectangle)) {
		// Cursor overlaps and left mouse button is clicked
		if (IsMouseButtonDown(0))
			// Only call onClick the first time
			if (!isClicked)
				onClick();
			else
				return;
		// Cursor overalps, button has isClicked flag, but mouse left is no longer down
		else if (isClicked)
			onRelease(true);
	}
	else {
		// Cursor does not overlap, mouse button is down and button has isClicked flag
		// Technically should only happen if You click the button and move the cursor off while still holding mouse left down
		if (IsMouseButtonDown(0) && isClicked)
			onRelease(false);
	}
}

void Button::draw() {

	checkSelfClick();
	DrawRectangleRec(rectangle, color);

	// Button border, will have a hardcoded size and be based on inverse of current color
	DrawRectangleLinesEx(rectangle, 2, colorAlt);

	// Button text - think of resizing issues for all of this later
	// Draws text in the middle of button rectangle, hardcoded for font size 20, make sure text length doesn't exceed button length!
	int textWidth = MeasureText(text.c_str(), 20);
	DrawText(text.c_str(), rectangle.x + (rectangle.width / 2) - (textWidth / 2), rectangle.y + (rectangle.height / 2) - 10, 20, BLACK);
}