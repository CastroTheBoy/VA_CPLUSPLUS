#ifndef COURSEWORK_IDRAWABLE
#define COURSEWORK_IDRAWABLE

#include "raylib.h"

namespace Coursework {

	class IDrawable {
	protected:
		IDrawable(bool isResizable) : isResizable(isResizable) {};
	
	public:

		bool isResizable;

		virtual void draw() = 0;
		virtual void resize() = 0;

		virtual ~IDrawable() {};

	};

}
#endif