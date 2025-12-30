#include <list>

#include "raylib.h"

#include "DrawableList.hpp"
#include "IDrawable.hpp"
#include "Helpers.hpp"

using namespace Coursework;

DrawableList::DrawableList(float topOffset, float bottomOffset, float listCenterWidthPercentage, DrawableListType alignmentType) :
	topOffsetPercentage(topOffset),
	bottomOffsetPercentage(bottomOffset),
	listCenterWidthPercentage(listCenterWidthPercentage),
	alignmentType(alignmentType)
{};

void DrawableList::addDrawable(IDrawable* drawable) {
	drawables.push_back(drawable);
	resize();
}

void DrawableList::draw() {	
	for (auto& i : drawables)
		i->draw();
}

// Replace all the function calls with variables
void DrawableList::resize() {
	int j = 1;
	int size = drawables.size();
	
	int firstHeight = 0;
	int lastHeight = 0;

	if (drawables.size() > 0) {
		firstHeight = drawables.front()->height;
		lastHeight = drawables.back()->height;
	}
	
	float topY = Helpers::round_to(GetScreenHeight() * topOffsetPercentage);
	float bottomY = Helpers::round_to(GetScreenHeight() - GetScreenHeight() * bottomOffsetPercentage) - lastHeight;

	int availableYLength = bottomY - topY - firstHeight - lastHeight;
	
	int intervalLength = 0;
	if(drawables.size() > 2)
		intervalLength = availableYLength / (drawables.size() - 2);

	for (auto& i : drawables) {
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

DrawableList::~DrawableList() {
	for (auto& i : drawables)
		delete i;
}