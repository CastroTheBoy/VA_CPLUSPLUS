#ifndef COURSEWORK_SLIDERBUTTON
#define COURSEWORK_SLIDERBUTTON

#include <utility>
#include <string>

#include "raylib.h"

#include "Button.hpp"
#include "EventHandler.hpp"
#include "Helpers.hpp"

using namespace Coursework;

namespace Coursework {

	class SliderButton : public Button {
	private:
		using CallbackTrigger = std::pair<EventType, std::function<void(EventType)>>;
		CallbackTrigger callbackOnIncrement;
		CallbackTrigger callbackOnDecrement;

		float checkBoxLineOffset = 4.5;
		float checkBoxLineWidth = 3;
		float outerBorderWidth = 2;
		float checkBoxBorderWidth = 2;

		Rectangle getGetSliderRectangle();
		
		void checkSelfClick();
		void onClick();
		void onSliderIncrement(bool fireCallback);
		void onSliderDecrement(bool fireCallback);

	public:
		bool isClicked = false;
		int incrementStepCount;

		SliderButton(float x, float y, float width, float height, Color color, Color colorAlt, std::string const& text, CallbackTrigger callbackOnIncrement, CallbackTrigger callbackOnDecrement);
		SliderButton(float x, float y, float width, float height, Color color, Color colorAlt, CallbackTrigger callbackOnIncrement, CallbackTrigger callbackOnDecrement);
		SliderButton(Rectangle rectangle, Color color, Color colorAlt, std::string const& text, CallbackTrigger callbackOnIncrement, CallbackTrigger callbackOnDecrement);
		SliderButton(Rectangle rectangle, Color color, Color colorAlt, CallbackTrigger callbackOnIncrement, CallbackTrigger callbackOnDecrement);

		// This is a UI element, so no copying/moving!
		SliderButton(const SliderButton&) = delete;
		SliderButton& operator=(const SliderButton&) = delete;

		void draw();

	};

}

#endif