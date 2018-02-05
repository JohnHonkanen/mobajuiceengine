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
			void Update();
			void LoopPointerEnterEvent();
			void AddPointerEnterEvent(class IPointerEnter *object);
		private:
			vector<class IPointerEnter *> pointerEnterObject;
			EventData data;
		};
	}
}