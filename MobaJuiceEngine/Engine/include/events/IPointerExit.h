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
		class IPointerExit : public IPointer {
		public:
			//Is called when event is true
			virtual void OnPointerExit(EventData data) = 0;
			//Checks if position contains our bounds
			bool Condition(glm::ivec2 position);
			void RegisterToEvents(HUD::HUDRect *in_bounds);
		private:
			bool inBounds = false;;
		};
	}
}