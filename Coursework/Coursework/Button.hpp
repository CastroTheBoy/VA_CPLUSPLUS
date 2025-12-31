#ifndef COURSEWORK_BUTTON
#define COURSEWORK_BUTTON

#include <string>

#include "raylib.h"

#include "IDrawable.hpp"

namespace Coursework {

	// A Button must be drawable, so by inheriting Button children must also provide their draw()'s
	class Button : public IDrawable {
	private:
		// Save base values for rescaling purposes, maybe only width and Height are needed
		float baseX;
		float baseY;
		float baseWidth;
		float baseHeight;

	protected:
		
		Button(float x, float y, float width, float height, Color color, Color colorAlt, std::string const& text) :
			x(x), y(y), width(width), height(height), baseX(x), baseY(y), baseWidth(width), baseHeight(height), color(color), colorAlt(colorAlt), text(text), fontSize(20), textColor(BLACK),
			// Kinda hacky, but I'm not going to rewrite the object structure again to solve this
			IDrawable(false) {
		};

	public:
		float x;
		float y;
		float height;
		float width;

		Rectangle getRectangle() {
			return { x, y, width, height };
		}

		// Only expose base values through a getter, to prevent them being changed
		Rectangle getBaseValues() {
			return { baseX, baseY, baseWidth, baseHeight };
		}

		// As base each button has access to two colors
		Color color;
		Color colorAlt;

		// Sample text that each button must have
		std::string text;
		float fontSize;
		Color textColor;

		virtual void draw() = 0;
		void resize() {};

		// This is a UI element, so no copying/moving!
		Button(const Button&) = delete;
		Button& operator=(const Button&) = delete;

		virtual ~Button() {};

	};

}

#endif