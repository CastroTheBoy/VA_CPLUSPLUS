#ifndef COURSEWORK_CHECKBOXBUTTON
#define COURSEWORK_CHECKBOXBUTTON

#include <utility>
#include <string>

#include "raylib.h"

#include "Button.hpp"
#include "EventHandler.hpp"
#include "Helpers.hpp"

namespace Coursework {

	class CheckboxButton : public Button {
	private:
		using CallbackTrigger = std::pair<EventType, std::function<void(EventType)>>;
		CallbackTrigger callbackOnRelease;

		void checkSelfClick();

		void onClick();
		void onRelease(bool fireCallbacks);

		float checkBoxLineOffset = 4.5;
		float checkBoxLineWidth = 3;
		float outerBorderWidth = 2;
		float checkBoxBorderWidth = 2;

		Rectangle getCheckBoxRectangle();

	public:
		bool isClicked = false;
		bool isChecked = false;

		CheckboxButton(float x, float y, float width, float height, Color color, Color colorAlt, std::string const& text, CallbackTrigger callbackOnRelease);
		CheckboxButton(float x, float y, float width, float height, Color color, Color colorAlt, CallbackTrigger callbackOnRelease);
		CheckboxButton(Rectangle rectangle, Color color, Color colorAlt, std::string const& text, CallbackTrigger callbackOnRelease);
		CheckboxButton(Rectangle rectangle, Color color, Color colorAlt, CallbackTrigger callbackOnRelease);

		// This is a UI element, so no copying/moving!
		CheckboxButton(const CheckboxButton&) = delete;
		CheckboxButton& operator=(const CheckboxButton&) = delete;

		void draw();

	};

}

#endif