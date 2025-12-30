#ifndef COURSEWORK_MENUSCREEN
#define COURSEWORK_MENUSCREEN

#include <forward_list>
#include <iostream>

#include "raylib.h"

#include "DrawableList.hpp"

namespace Coursework {

	// Use this for a UI screen that requires buttons
	class MenuScreen {
	private:
		std::forward_list<DrawableList*> drawables;

	public:
		Color Background;
		Camera2D camera;

		MenuScreen(Color color);
		MenuScreen(Color color, Camera2D camera);

		void addDrawableList(DrawableList* drawableList);

		void drawScreen();
		void resizeDrawables();

		~MenuScreen();
	};

}

#endif