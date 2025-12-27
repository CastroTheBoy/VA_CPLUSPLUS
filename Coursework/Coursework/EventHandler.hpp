#ifndef COURSEWORK_EVENTHANDLER
#define COURSEWORK_EVENTHANDLER

#include <forward_list>
#include <unordered_map>
#include <functional>

namespace Coursework {

	enum EventType {
		MAIN_MENU_SETTING_ON_RELEASE,
		MAIN_MENU_EXIT_ON_RELEASE,
		MAIN_MENU_START_ON_RELEASE,
		SETTING_RETURN_ON_RELEASE
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