#ifndef COURSEWORK_ICLICKABLE
#define COURSEWORK_ICLICKABLE

namespace Coursework {

	class IClickable {
	public:
		virtual void onClick() = 0;
		virtual void onRelease(bool fireCallbacks) = 0;
	};

}
#endif