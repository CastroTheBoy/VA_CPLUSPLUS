#include <string>

#include "raylib.h"

#include "CheckboxButton.hpp"
#include "EventHandler.hpp"
#include "Helpers.hpp"

using namespace Coursework;

Rectangle CheckboxButton::getCheckBoxRectangle() {
	return { static_cast<float>(x + (width - height)), y, height, height };
}

void CheckboxButton::checkSelfClick() {
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


void CheckboxButton::onClick() {
	isClicked = true;
}

void CheckboxButton::onRelease(bool fireCallbacks) {
	isClicked = false;
	isChecked = !isChecked;
	if (fireCallbacks)
		callbackOnRelease.second(callbackOnRelease.first);
}

CheckboxButton::CheckboxButton(
	float x, float y, float width, float height, Color color, Color colorAlt, std::string const& text, CallbackTrigger callbackOnRelease
) :
	Button(x, y, width, height, color, colorAlt, text)
	, callbackOnRelease(callbackOnRelease) {
};

CheckboxButton::CheckboxButton(float x, float y, float width, float height, Color color, Color colorAlt, CallbackTrigger callbackOnRelease) :
	CheckboxButton(x, y, width, height, color, colorAlt, "", callbackOnRelease) {
};

CheckboxButton::CheckboxButton(Rectangle rec, Color color, Color colorAlt, std::string const& text, CallbackTrigger callbackOnRelease) :
	CheckboxButton(rec.x, rec.y, rec.width, rec.height, color, colorAlt, text, callbackOnRelease) {
};

CheckboxButton::CheckboxButton(Rectangle rec, Color color, Color colorAlt, CallbackTrigger callbackOnRelease) :
	CheckboxButton(rec, color, colorAlt, "", callbackOnRelease) {
};

void CheckboxButton::draw() {

	Rectangle recOutsideBox = getRectangle();
	Rectangle recCheckBox = getCheckBoxRectangle();

	checkSelfClick();
	DrawRectangleRec(recOutsideBox, color);

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
	int textWidth = MeasureText(text.c_str(), fontSize);
	DrawText(text.c_str(), recOutsideBox.x + 5, recOutsideBox.y + (recOutsideBox.height / 2) - 10, fontSize, textColor);
}