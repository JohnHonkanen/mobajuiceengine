#pragma once
#include "EventData.h"
#include <glm\glm.hpp>
namespace Engine
{
	namespace HUD
	{
		struct HUDRect;
	}

	namespace Events
	{
		class IPointer
		{
		public:
			//Check if our condition passes
			virtual bool Condition(glm::ivec2 position, EventData data) = 0;
			//Register ourselves to the appropriate event
			virtual void RegisterToEvents(HUD::HUDRect *in_bounds) = 0;
		protected:
			//Checks if point is in our bounds
			virtual bool Contains(glm::ivec2 position);
			//Bounds of the Ipointer rect
			HUD::HUDRect *bounds;
		};
	}
}