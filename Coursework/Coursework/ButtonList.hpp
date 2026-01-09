#ifndef COURSEWORK_BUTTONLIST
#define COURSEWORK_BUTTONLIST

#include <list>

#include "raylib.h"

#include "Button.hpp"
#include "IDrawable.hpp"
#include "Helpers.hpp"

namespace Coursework {

	enum ButtonListType { JUSTIFIED, TOP, BOTTOM };

	class ButtonList : public IDrawable {

	private:
		std::list<Button*> buttons;

		float topOffsetPercentage;
		float bottomOffsetPercentage;
		float listCenterWidthPercentage;

	public:

		ButtonListType alignmentType;

		ButtonList(float topOffset, float bottomOffset, float listCenterWidthPercentage, ButtonListType alignmentType);

		void addButton(Button* drawable);
	
		void draw();

		void resize();

		~ButtonList();

	};
}

#endif