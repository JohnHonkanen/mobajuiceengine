#pragma once
#include "EventData.h"
#include "hud\HUDRect.h"

#include <glm\glm.hpp>
namespace Engine
{
	namespace Events
	{
		class IPointerEnter {
		public:
			//Is called when event is true
			virtual void OnPointerEnter(EventData data) = 0;
			//Checks if position contains our bounds
			bool Contains(glm::vec2 position) { return bounds.Contains(position.x, position.y); };
			void RegisterToEvents(Engine::HUD::HUDRect in_bounds);
		private:
			Engine::HUD::HUDRect bounds;
		};
	}
}