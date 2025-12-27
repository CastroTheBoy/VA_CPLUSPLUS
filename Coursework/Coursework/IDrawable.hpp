#ifndef COURSEWORK_IDRAWABLE
#define COURSEWORK_IDRAWABLE

#include "raylib.h"

namespace Coursework {

	// Think a bit on this, maybe expand and make screen specific to use in UIManager to handle different (menu and game) screens
	class IDrawable {
	public:
		virtual void draw() = 0;
	};

}
#endif