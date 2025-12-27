#include "raylib.h"
#include "Button.hpp"

Coursework::Button::Button(int x, int y, int width, int height, Color colorStandard, Color colorHighlight, std::string const& text) :
	color(colorStandard), colorAlt(colorHighlight), colorStandard(colorStandard), colorHighlight(colorHighlight), text(text)
{
	this->rectangle = Rectangle(x, y, width, height);
}

Coursework::Button::Button(int x, int y, int width, int height, Color colorStandard, Color colorHighlight) : 
	Button(x, y, width, height, colorStandard, colorHighlight, "") {};

void Coursework::Button::onClick() {
	this->isClicked = true;
	this->color = this->colorHighlight;
	this->colorAlt = this->colorStandard;
}

void Coursework::Button::addOnReleaseCallback(std::function<void()> callback) {
	callbacks.push_front(callback);
}

void Coursework::Button::onRelease(bool fireCallbacks) {
	this->isClicked = false;
	// Again, just reference the base values
	this->color = this->colorStandard;
	this->colorAlt = this->colorHighlight;
	// I have a feeling this should be asynched somehow
	if(fireCallbacks)
		for (auto& i : callbacks)
			i();
}