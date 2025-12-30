#ifndef COURSEWORK_BUTTONLIST
#define COURSEWORK_BUTTONLIST

#include <list>

#include "raylib.h"

#include "IDrawable.hpp"
#include "Helpers.hpp"

using namespace Coursework;

enum DrawableListType { JUSTIFIED, TOP, BOTTOM };

class DrawableList {

private:
	std::list<IDrawable*> drawables;

	float topOffsetPercentage;
	float bottomOffsetPercentage;
	float listCenterWidthPercentage;

public:

	DrawableListType alignmentType;

	DrawableList(float topOffset, float bottomOffset, float listCenterWidthPercentage, DrawableListType alignmentType);

	void addDrawable(IDrawable* drawable);
	
	void draw();
	void resize();

	~DrawableList();

};
#endif