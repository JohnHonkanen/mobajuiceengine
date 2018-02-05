#pragma once
#include "EventData.h"
#include "IPointer.h"
#include <glm\glm.hpp>


namespace Engine
{
	namespace HUD
	{
		class HUDRect;
	}

	namespace Events
	{
		class IPointerEnter: public IPointer {
		public:
			//Is called when event is true
			virtual void OnPointerEnter(EventData data) = 0;
			//Checks if position contains our bounds
			bool Condition(glm::ivec2 position);
			void RegisterToEvents(HUD::HUDRect *in_bounds);
		private:
			bool inBounds = false;;
		};
	}
}