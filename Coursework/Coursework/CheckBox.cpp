#include <utility>
#include <string>
#include <iostream>

#include "raylib.h"

#include "Checkbox.hpp"
#include "IClickable.hpp"
#include "IDrawable.hpp"
#include "EventHandler.hpp"
#include "Helpers.hpp"

using namespace Coursework;

Rectangle Checkbox::getCheckBoxRectangle() {
	return { static_cast<float>(x + (width - height)), y, height, height };
}

Rectangle Checkbox::getOuterRectangle() {
	return { x, y, width, height };
}

void Checkbox::checkSelfClick() {
	if (CheckCollisionPointRec(GetMousePosition(), getCheckBoxRectangle())) {
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


void Checkbox::onClick() {
	isClicked = true;
	std::cout << text << " - onClick" << '\n';
}

void Checkbox::onRelease(bool fireCallbacks) {
	isClicked = false;
	isChecked = !isChecked;
	// Again, just reference the base values
	std::cout << text << " - onRelease" << '\n';
	if (fireCallbacks)
		callbackTrigger.second(callbackTrigger.first);
}

Checkbox::Checkbox(float x, float y, float width, float height, Color colorStandard, Color colorHighlight, std::string const& text, CallbackTrigger callback) :
	IDrawable(x, y, width, height),
	colorStandard(colorStandard), colorAlt(colorHighlight), text(text), callbackTrigger(callback) {
};

void Checkbox::draw() {

	Rectangle recOutsideBox = getOuterRectangle();
	Rectangle recCheckBox = getCheckBoxRectangle();

	checkSelfClick();
	DrawRectangleRec(recOutsideBox, colorStandard);

	// Button border, will have a hardcoded size and be based on inverse of current color
	DrawRectangleLinesEx(recOutsideBox, outerBorderWidth, colorAlt);

	if (!isClicked)
		DrawRectangleRec(recCheckBox, colorAlt);
	else
		DrawRectangleRec(recCheckBox, Helpers::changeColorDarkness(colorAlt, 0.8));

	DrawRectangleLinesEx(recCheckBox, checkBoxBorderWidth, BLACK);

	if (isChecked) {
		DrawLineEx(
			{ recCheckBox.x + checkBoxLineOffset, recCheckBox.y + checkBoxLineOffset },
			{ recCheckBox.x + recCheckBox.height - checkBoxLineOffset, recCheckBox.y + recCheckBox.height - checkBoxLineOffset },
			checkBoxLineWidth,
			WHITE
		);
		DrawLineEx(
			{ recCheckBox.x + recCheckBox.width - checkBoxLineOffset, recCheckBox.y + checkBoxLineOffset },
			{ recCheckBox.x + checkBoxLineOffset, recCheckBox.y + recCheckBox.height - checkBoxLineOffset },
			checkBoxLineWidth,
			WHITE
		);
	}

	// Button text - think of resizing issues for all of this later
	// Draws text in the middle of button rectangle, hardcoded for font size 20, make sure text length doesn't exceed button length!
	int textWidth = MeasureText(text.c_str(), 20);
	DrawText(text.c_str(), recOutsideBox.x + 5, recOutsideBox.y + (recOutsideBox.height / 2) - 10, 20, BLACK);
}