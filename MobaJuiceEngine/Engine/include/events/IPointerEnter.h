#pragma once
#include "IPointer.h"
#include <glm\glm.hpp>


namespace Engine
{
	namespace HUD
	{
		struct HUDRect;
	}

	namespace Events
	{
		class IPointerEnter: public IPointer {
		public:
			//Is called when event is true
			virtual void OnPointerEnter(EventData data) = 0;
			//Checks if condition is passed
			bool Condition(glm::ivec2 position, EventData data);
			void RegisterToEvents(HUD::HUDRect *in_bounds);
		private:
			bool inBounds = false;;
		};
	}
}