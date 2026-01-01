#ifndef COURSEWORK_EVENTHANDLER
#define COURSEWORK_EVENTHANDLER

#include <forward_list>
#include <unordered_map>
#include <functional>

namespace Coursework {

	enum EventType {
		DUMMY_EVENT,
		MAIN_MENU_SETTING_ON_RELEASE,
		MAIN_MENU_EXIT_ON_RELEASE,
		MAIN_MENU_START_ON_RELEASE,
		SETTING_RETURN_ON_RELEASE,
		SETTING_FULLSCREEN_ON_RELEASE,
		SCREEN_RESIZE_1920_1080,
		SCREEN_RESIZE_800_600,
		SLIDER_INCREMENT_1,
		SLIDER_INCREMENT_2,
		SLIDER_DECREMENT_1,
		SLIDER_DECREMENT_2
	};

	// A very, very crude implementation
	class EventHandler {
	private:
		// for now write callbacks so they're parameterless, in the future can add Event type classes with data
		using Callback = std::function<void()>;
		std::unordered_map<EventType, std::forward_list<Callback>> callbacks;

	public:

		EventHandler() = default;

		void fireEvent(EventType type);

		void addCallback(EventType type, Callback callback);

	};
}
#endif