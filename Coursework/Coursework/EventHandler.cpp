#include <forward_list>
#include <unordered_map>
#include <functional>

#include "EventHandler.hpp"

// I have a feeling I will be rewriting all of this, but that sounds like a future me problem

using namespace Coursework;

void EventHandler::fireEvent(EventType type) {
	for (auto& i : callbacks[type])
	i();
}

// Adding remove requires some kind of identifier for each function, which I am too lazy to implement right now
// So no remove!
void EventHandler::addCallback(EventType type, Callback callback) {
	callbacks[type].push_front(callback);
}