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

	class Button : public IClickable, public IDrawable {
	
	private:
		// At this point why not just expose these two? Rewrite plz.
		Color colorStandard;
		Color colorHighlight;
		using CallbackTrigger = std::pair<EventType, std::function<void(EventType)>>;
		CallbackTrigger callbackTrigger;

		void checkSelfClick();

		void onClick();
		void onRelease(bool fireCallbacks);

		Rectangle getRectangle();

	public:
		Color color;
		Color colorAlt;
		std::string text;
		bool isClicked = false;

		Button(float x, float y, float width, float height, Color colorStandard, Color colorHighlight, CallbackTrigger callback);
		Button(float x, float y, float width, float height, Color colorStandard, Color colorHighlight, std::string const& text, CallbackTrigger callback);

		virtual void draw();
	};

}
#endif