#pragma once
#include <vector>
#include "EventData.h"

using namespace std;
namespace Engine
{
	namespace Events
	{
		class EventManager
		{
		public:
			enum IPOINTER_EVENT {
				ENTER,
				EXIT,
				MOUSE_DOWN,
				MOUSE_UP,
				ON_DRAG
			};
			void Update();
			void LoopIPointerEvents();
			void AddIPointerEvent(IPOINTER_EVENT type, class IPointer *eventObject);
		private:
			vector<class IPointerEnter *> pointerEnterObject;
			vector<class IPointerExit *> pointerExitObject;
			EventData data;
		};
	}
}