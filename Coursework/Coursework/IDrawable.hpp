#ifndef COURSEWORK_IDRAWABLE
#define COURSEWORK_IDRAWABLE

#include "raylib.h"

namespace Coursework {

	class IDrawable {
	public:
		float x;
		float y;
		float height;
		float width;

		virtual void draw() = 0;

		virtual ~IDrawable() {};

		IDrawable(float x, float y, float width, float height) : x(x), y(y), width(width), height(height) {};

	};

}
#endif