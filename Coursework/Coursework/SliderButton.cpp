#include <cmath>

#include "raylib.h"

#include "SliderButton.hpp"
#include "Helpers.hpp"

using namespace Coursework;

Rectangle SliderButton::getGetSliderRectangle() {
	return { static_cast<float>(x + (width - height)), y, height, height };
}

void SliderButton::checkSelfClick() {
	Rectangle sliderBarBox = getSliderBarBox();
	text = std::to_string(currentIncrenemnt).append(", ").append(std::to_string(incrementStepCount));
	if (CheckCollisionPointRec(GetMousePosition(), getSliderBarBox())) {
		// Cursor overlaps and left mouse button is clicked
		if (IsMouseButtonDown(0)) {
			// Only call onClick the first time
			if (!isClicked) {
				onClick();
				return;
			}
		}
	}
	else if (isClicked) {
		if (!IsMouseButtonDown(0)) {
			onRelease();
			return;
		}
		if (GetMouseX() > (sliderBarBox.x + sliderBarBox.width / 2)) {
			onSliderIncrement(true);
			return;
		}
		if (GetMouseX() < (sliderBarBox.x - sliderBarBox.width / 2)) {
			onSliderDecrement(true);
			return;
		}
	}
}


void SliderButton::onClick() {
	isClicked = true;
}

void SliderButton::onRelease() {
	isClicked = false;
}

void SliderButton::onSliderIncrement(bool fireCallback) {
	if (currentIncrenemnt + 1 > incrementStepCount)
		return;

	currentIncrenemnt = std::min(currentIncrenemnt + 1, incrementStepCount);
	if (fireCallback)
		callbackOnIncrement.second(callbackOnIncrement.first);
}

void SliderButton::onSliderDecrement(bool fireCallback) {
	if (currentIncrenemnt - 1 < 0)
		return;
	currentIncrenemnt = std::max(currentIncrenemnt - 1, 0);
	if (fireCallback)
		callbackOnDecrement.second(callbackOnDecrement.first);
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

// Add overrides to pass required Rectangle by ref to limit function calls
Rectangle SliderButton::getSliderBox() {
	Rectangle recOutsideBox = getRectangle();
	return { recOutsideBox.x + 5, recOutsideBox.y + recOutsideBox.height * 0.3f, recOutsideBox.width - 10, recOutsideBox.height * 0.6f };
}

Rectangle SliderButton::getSliderBar() {
	Rectangle recSliderBox = getSliderBox();
	return { recSliderBox.x + 3, recSliderBox.y + recSliderBox.height / 2 - recSliderBox.height * 0.3f / 2, recSliderBox.width - 6, recSliderBox.height * 0.3f };
}

Rectangle SliderButton::getSliderBarBox() {
	Rectangle recSlideBar = getSliderBar();
	Rectangle recSliderBox = getSliderBox();
	float barWidth = Helpers::round_to(recSlideBar.width / 15, 0.01);
	float incrementLength = (recSlideBar.width - barWidth) / incrementStepCount;
	return { recSlideBar.x + incrementLength * currentIncrenemnt, recSliderBox.y + 3, barWidth, recSliderBox.height - 6 };
}

void SliderButton::draw() {

	Rectangle recOutsideBox = getRectangle();
	Rectangle recSliderBox = getSliderBox();
	Rectangle recSlideBar = getSliderBar();
	Rectangle recSlideBarBox = getSliderBarBox();


	checkSelfClick();
	DrawRectangleRec(recOutsideBox, color);

	// Button border, will have a hardcoded size and be based on inverse of current color
	DrawRectangleLinesEx(recOutsideBox, outerBorderWidth, colorAlt);

	DrawRectangleRec(recSliderBox, colorAlt);
	DrawRectangleLinesEx(recSliderBox, outerBorderWidth, Helpers::changeColorDarkness(colorAlt, 0.9));

	DrawRectangleRec(recSlideBar, Helpers::changeColorDarkness(colorAlt, 0.70));


	DrawRectangleRec(recSlideBarBox, Helpers::changeColorDarkness(color, 1.1));
	DrawRectangleLinesEx(recSlideBarBox, outerBorderWidth, Helpers::changeColorDarkness(color, 0.8));


	// Button text - think of resizing issues for all of this later
	// Draws text in the middle of button rectangle, hardcoded for font size 20, make sure text length doesn't exceed button length!
	int textWidth = MeasureText(text.c_str(), 20);
	DrawText(text.c_str(), x + (width / 2) - (textWidth / 2), recOutsideBox.y + 5, 20, BLACK);
}