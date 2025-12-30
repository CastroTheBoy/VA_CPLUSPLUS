#include <forward_list>

#include "raylib.h"

#include "MenuScreen.hpp"

using namespace Coursework;

MenuScreen::MenuScreen(Color color) : Background(color)
{
	this->camera.offset.x = 0;
	this->camera.offset.y = 0;
	this->camera.target.x = 0;
	this->camera.target.y = 0;
	this->camera.rotation = 0;
	this->camera.zoom = 1;
};

MenuScreen::MenuScreen(Color color, Camera2D camera) : Background(color), camera(camera) {};
		
// I can't imagine a scenario where I would remove a button, so no removeButtion()
void MenuScreen::addDrawableList(DrawableList *drawable) {
	drawables.push_front(drawable);
}
	
// Call this after BeginDrawing to draw the screen and it's contents
// Screen will always draw relative to screen coordinates and not world, so use only for UI type drawables
void MenuScreen::drawScreen() {
	//checkButtonClick();

	BeginMode2D(this->camera);

	// Draw menu background, ideally this has an alpha <255, especially if it's a pause menu screen
	DrawRectangleRec({0, 0, static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight())}, this->Background);

	for (auto& i : drawables) {
		i->draw();
	}

	EndMode2D();
}

MenuScreen::~MenuScreen()
{
	for (auto& i : drawables)
		delete i;
};

void MenuScreen::resizeDrawables() {
	for (auto& i : drawables)
		i->resize();;
}