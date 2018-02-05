#include "events\IPointerMouseDown.h"
namespace Engine
{
	namespace Events
	{
		bool IPointerMouseDown::Condition(glm::ivec2 position, EventData data)
		{
			return false;
		}
		void IPointerMouseDown::RegisterToEvents(HUD::HUDRect * in_bounds)
		{
		}
	}
}