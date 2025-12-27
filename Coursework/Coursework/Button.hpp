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

namespace Coursework {

	class Button : IClickable {
	
	private:
		// At this point why not just expose these two? Rewrite plz.
		Color colorStandard;
		Color colorHighlight;
		// Write callback functions in such a way that they're void and paramaterless
		std::forward_list<std::function<void()>> callbacks;

	public:
		Color color;
		Color colorAlt;
		std::string text;
		Rectangle rectangle;
		bool isClicked = false;

		Button(int x, int y, int width, int height, Color colorStandard, Color colorHighlight);
		Button(int x, int y, int width, int height, Color colorStandard, Color colorHighlight, std::string const& text);

		void onClick();

		void addOnReleaseCallback(std::function<void()> callback);

		void onRelease(bool fireCallbacks);

	};

}
#endif