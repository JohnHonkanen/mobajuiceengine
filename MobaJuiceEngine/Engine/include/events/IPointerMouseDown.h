#pragma once
#include "IPointer.h"
namespace Engine
{
	namespace Events
	{
		class IPointerMouseDown : public IPointer
		{
		public:
			//Is called when event is true
			virtual void OnPointerMouseDown(EventData data) = 0;
			//Checks if position contains our bounds
			bool Condition(glm::ivec2 position, EventData data);
			void RegisterToEvents(HUD::HUDRect *in_bounds);
		private:
			bool inBounds = false;
		};
	}
}