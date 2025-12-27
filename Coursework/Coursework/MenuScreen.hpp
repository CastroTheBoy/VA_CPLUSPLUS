#ifndef COURSEWORK_MENUSCREEN
#define COURSEWORK_MENUSCREEN

#include <forward_list>
#include <iostream>

#include "raylib.h"

#include "Button.hpp"

namespace Coursework {

	// Use this for a UI screen that requires buttons
	class MenuScreen {
	private:
		std::forward_list<Button*> buttons;

		Rectangle recGetWorldToScreen2D(Rectangle* rec);

	public:
		Color Background;
		Camera2D camera;

		MenuScreen(Color color);
		MenuScreen(Color color, Camera2D camera);

		void addButton(Button* button);

		void drawScreen();

		~MenuScreen();
	};

}

#endif