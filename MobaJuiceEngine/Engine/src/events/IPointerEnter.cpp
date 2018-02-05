#include "events\IPointerEnter.h"
#include "core\GameEngine.h"
namespace Engine
{
	namespace Events
	{
		bool IPointerEnter::Condition(glm::ivec2 position, EventData data)
		{
			bool pointerInBounds = Contains(position);

			if (pointerInBounds)
			{
				if (!inBounds)
				{
					inBounds = true;
					return true;
				}

				return false;
			}
			else
			{
				inBounds = false;
				return false;
			}

		}
		void IPointerEnter::RegisterToEvents(HUD::HUDRect * in_bounds)
		{
			bounds = in_bounds;

			GameEngine::manager.eventManager.AddIPointerEvent(EventManager::ENTER, this);
		}
	}
}