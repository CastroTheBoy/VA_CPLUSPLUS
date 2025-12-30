#ifndef COURSEWORK_CHECKBOX
#define COURSEWORK_CHECKBOX

#include <utility>
#include <string>
#include <iostream>

#include "raylib.h"

#include "IClickable.hpp"
#include "IDrawable.hpp"
#include "EventHandler.hpp"
#include "Helpers.hpp"

using namespace Coursework;

class Checkbox : public IClickable, public IDrawable {
private:
	using CallbackTrigger = std::pair<EventType, std::function<void(EventType)>>;
	CallbackTrigger callbackTrigger;

	float checkBoxLineOffset = 4.5;
	float checkBoxLineWidth = 3;
	float outerBorderWidth = 2;
	float checkBoxBorderWidth = 2;

	Rectangle getCheckBoxRectangle();
	Rectangle getOuterRectangle();

	void checkSelfClick();
	void onClick();
	void onRelease(bool fireCallbacks);

public:
	Color colorStandard;
	Color colorAlt;
	std::string text;
	bool isClicked = false;
	bool isChecked = false;

	Checkbox(float x, float y, float width, float height, Color colorStandard, Color colorHighlight, std::string const& text, CallbackTrigger callback);

	void draw();

};

#endif