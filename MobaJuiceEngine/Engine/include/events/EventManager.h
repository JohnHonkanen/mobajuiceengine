#pragma once
#include <vector>
#include "IPointerEnter.h"
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
			void AddPointerEnterEvent(IPointerEnter *object);
		private:
			vector<IPointerEnter *> pointerEnterObject;
			EventData data;
		};
	}
}