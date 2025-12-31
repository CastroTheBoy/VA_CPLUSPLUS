#ifndef COURSEWORK_SIMPLEBUTTON
#define COURSEWORK_SIMPLEBUTTON

#include <string>
#include <functional>
#include <utility>

#include "raylib.h"

#include "Button.hpp"
#include "EventHandler.hpp"

namespace Coursework {

	// Basic clickable button where entire button space is clickable space
	// Callback will be fired on click release
	class SimpleButton : public Button {
	
	private:
		using CallbackTrigger = std::pair<EventType, std::function<void(EventType)>>;
		CallbackTrigger callbackOnRelease;

		void checkSelfClick();

		void onClick();
		void onRelease(bool fireCallbacks);

	public:
		bool isClicked = false;

		SimpleButton(float x, float y, float width, float height, Color color, Color colorAlt, std::string const& text, CallbackTrigger callbackOnRelease);
		SimpleButton(float x, float y, float width, float height, Color color, Color colorAlt, CallbackTrigger callbackOnRelease);
		SimpleButton(Rectangle rectangle, Color color, Color colorAlt, std::string const& text, CallbackTrigger callbackOnRelease);
		SimpleButton(Rectangle rectangle, Color color, Color colorAlt, CallbackTrigger callbackOnRelease);

		// This is a UI element, so no copying/moving!
		SimpleButton(const SimpleButton&) = delete;
		SimpleButton& operator=(const SimpleButton&) = delete;

		void draw();

		~SimpleButton() {};
	};

}
#endif