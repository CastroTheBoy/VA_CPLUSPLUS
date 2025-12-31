#include <iostream>

#include "raylib.h"

#include "SimpleButton.hpp"
#include "Helpers.hpp"
#include "Button.hpp"

using namespace Coursework;

SimpleButton::SimpleButton(
	float x, float y, float width, float height, Color color, Color colorAlt, std::string const& text, CallbackTrigger callbackOnRelease
) :
	Button(x, y, width, height, color, colorAlt, text)
	, callbackOnRelease(callbackOnRelease) {};

SimpleButton::SimpleButton(float x, float y, float width, float height, Color color, Color colorAlt, CallbackTrigger callbackOnRelease) :
	SimpleButton(x, y, width, height, color, colorAlt, "", callbackOnRelease) {};

SimpleButton::SimpleButton(Rectangle rec, Color color, Color colorAlt, std::string const& text, CallbackTrigger callbackOnRelease) :
	SimpleButton(rec.x, rec.y, rec.width, rec.height, color, colorAlt, text, callbackOnRelease) {
};

SimpleButton::SimpleButton(Rectangle rec, Color color, Color colorAlt, CallbackTrigger callbackOnRelease) :
	SimpleButton(rec, color, colorAlt, "", callbackOnRelease) {
};

void SimpleButton::onClick() {
	isClicked = true;
}

void SimpleButton::onRelease(bool fireCallbacks) {
	isClicked = false;
	if (fireCallbacks)
		callbackOnRelease.second(callbackOnRelease.first);
}

void SimpleButton::checkSelfClick() {
	if (CheckCollisionPointRec(GetMousePosition(), getRectangle())) {
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

void SimpleButton::draw() {

	checkSelfClick();
	DrawRectangleRec(getRectangle(), isClicked ? colorAlt : color);

	// Button border, will have a hardcoded size and be based on inverse of current color
	DrawRectangleLinesEx(getRectangle(), 2, isClicked ? color : colorAlt);

	// Button text - think of resizing issues for all of this later
	// Draws text in the middle of button rectangle, hardcoded for font size 20, make sure text length doesn't exceed button length!
	int textWidth = MeasureText(text.c_str(), fontSize);
	DrawText(text.c_str(), x + (width / 2) - (textWidth / 2), y + (height / 2) - 10, fontSize, textColor);
}