#include "raylib.h"

#include "SliderButton.hpp"

using namespace Coursework;

Rectangle SliderButton::getGetSliderRectangle() {
	return { static_cast<float>(x + (width - height)), y, height, height };
}

void SliderButton::checkSelfClick() {
	if (CheckCollisionPointRec(GetMousePosition(), getRectangle())) {
		// Cursor overlaps and left mouse button is clicked
		if (IsMouseButtonDown(0))
			// Only call onClick the first time
			if (!isClicked)
				onClick();
			else
				return;
		// Cursor overalps, button has isClicked flag, but mouse left is no longer down
		//else if (isClicked)
			//onRelease(true);
	}
	else {
		// Cursor does not overlap, mouse button is down and button has isClicked flag
		// Technically should only happen if You click the button and move the cursor off while still holding mouse left down
		//if (IsMouseButtonDown(0) && isClicked)
			//onRelease(false);
	}
}


void SliderButton::onClick() {
	isClicked = true;
}

void SliderButton::onSliderIncrement(bool fireCallback) {
	isClicked = false;
	if (fireCallback)
		callbackOnIncrement.second(callbackOnIncrement.first);
}


void SliderButton::onSliderDecrement(bool fireCallback) {
	isClicked = false;
	if (fireCallback)
		callbackOnIncrement.second(callbackOnIncrement.first);
}

SliderButton::SliderButton(
	float x, float y, float width, float height, Color color, Color colorAlt, std::string const& text, CallbackTrigger callbackOnIncrement, CallbackTrigger callbackOnDecrement
) :
	Button(x, y, width, height, color, colorAlt, text)
	, callbackOnIncrement(callbackOnIncrement), callbackOnDecrement(callbackOnDecrement){
};

SliderButton::SliderButton(float x, float y, float width, float height, Color color, Color colorAlt, CallbackTrigger callbackOnIncrement, CallbackTrigger callbackOnDecrement) :
	SliderButton(x, y, width, height, color, colorAlt, "", callbackOnIncrement, callbackOnDecrement) {
};

SliderButton::SliderButton(Rectangle rec, Color color, Color colorAlt, std::string const& text, CallbackTrigger callbackOnIncrement, CallbackTrigger callbackOnDecrement) :
	SliderButton(rec.x, rec.y, rec.width, rec.height, color, colorAlt, text, callbackOnIncrement, callbackOnDecrement) {
};

SliderButton::SliderButton(Rectangle rec, Color color, Color colorAlt, CallbackTrigger callbackOnIncrement, CallbackTrigger callbackOnDecrement) :
	SliderButton(rec, color, colorAlt, "", callbackOnIncrement, callbackOnDecrement) {
};

void SliderButton::draw() {

	Rectangle recOutsideBox = getRectangle();

	checkSelfClick();
	DrawRectangleRec(recOutsideBox, color);

	// Button border, will have a hardcoded size and be based on inverse of current color
	DrawRectangleLinesEx(recOutsideBox, outerBorderWidth, colorAlt);

	// Button text - think of resizing issues for all of this later
	// Draws text in the middle of button rectangle, hardcoded for font size 20, make sure text length doesn't exceed button length!
	int textWidth = MeasureText(text.c_str(), 20);
	DrawText(text.c_str(), recOutsideBox.x + 5, recOutsideBox.y + (recOutsideBox.height / 2) - 10, 20, BLACK);
}