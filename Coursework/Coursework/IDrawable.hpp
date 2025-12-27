#ifndef COURSEWORK_IDRAWABLE
#define COURSEWORK_IDRAWABLE

#include "raylib.h"

namespace Coursework {

	class IDrawable {
	public:
		virtual void draw() = 0;
	};

}
#endif