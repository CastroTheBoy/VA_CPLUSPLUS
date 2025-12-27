#ifndef COURSEWORK_BUTTON
#define COURSEWORK_BUTTON

#include <string>
#include <functional>
#include <forward_list>
#include <utility>
#include <iostream>

#include "raylib.h"

#include "IClickable.hpp"
#include "IDrawable.hpp"
#include "EventHandler.hpp"

namespace Coursework {

	class Button : IClickable {
	
	private:
		// At this point why not just expose these two? Rewrite plz.
		Color colorStandard;
		Color colorHighlight;
		// Maybe also just pass a bind 
		using CallbackTrigger = std::pair<EventType, std::function<void(EventType)>>;
		CallbackTrigger callbackTrigger;

		void checkSelfClick();

	public:
		Color color;
		Color colorAlt;
		std::string text;
		Rectangle rectangle;
		bool isClicked = false;

		Button(int x, int y, int width, int height, Color colorStandard, Color colorHighlight, CallbackTrigger callback);
		Button(int x, int y, int width, int height, Color colorStandard, Color colorHighlight, std::string const& text, CallbackTrigger callback);

		void onClick();
		void onRelease(bool fireCallbacks);

		void draw();

	};

}
#endif