#include <list>

#include "raylib.h"

#include "ButtonList.hpp"
#include "IDrawable.hpp"
#include "Helpers.hpp"

using namespace Coursework;

ButtonList::ButtonList(float topOffset, float bottomOffset, float listCenterWidthPercentage, ButtonListType alignmentType) :
	topOffsetPercentage(topOffset),
	bottomOffsetPercentage(bottomOffset),
	listCenterWidthPercentage(listCenterWidthPercentage),
	alignmentType(alignmentType),
	IDrawable(true)
{};

void ButtonList::addButton(Button* button) {
	buttons.push_back(button);
	resize();
}

void ButtonList::draw() {
	for (auto& i : buttons)
		i->draw();
}

// Replace all the function calls with variables
void ButtonList::resize() {
	int j = 1;
	int size = buttons.size();
	
	int firstHeight = 0;
	int lastHeight = 0;

	if (buttons.size() > 0) {
		firstHeight = buttons.front()->height;
		lastHeight = buttons.back()->height;
	}
	
	float topY = Helpers::round_to(GetScreenHeight() * topOffsetPercentage);
	float bottomY = Helpers::round_to(GetScreenHeight() - GetScreenHeight() * bottomOffsetPercentage) - lastHeight;

	int availableYLength = bottomY - topY - firstHeight - lastHeight;
	
	int intervalLength = 0;
	if(buttons.size() > 2)
		intervalLength = availableYLength / (buttons.size() - 2);

	for (auto& i : buttons) {
		if (j == 1) {
			i->x = (GetScreenWidth() * listCenterWidthPercentage) - i->width / 2;
			i->y = topY;
		}
		else if (j == size) {
			i->x = (GetScreenWidth() * listCenterWidthPercentage) - i->width / 2;
			i->y = bottomY;

		}
		else {
			i->x = (GetScreenWidth() * listCenterWidthPercentage) - i->width / 2;
			i->y = topY + firstHeight + (intervalLength / 2) * (j - 1);
		}
		j++;
	}
}

ButtonList::~ButtonList() {
	for (auto& i : buttons)
		delete i;
}