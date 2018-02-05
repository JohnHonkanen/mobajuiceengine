#include "events\IPointerExit.h"
#include "core\GameEngine.h"
namespace Engine
{
	namespace Events
	{
		bool IPointerExit::Condition(glm::ivec2 position)
		{
			bool pointerInBounds = Contains(position);

			if (pointerInBounds)
			{
				inBounds = true;
				return false;
			}
			else
			{
				if (inBounds)
				{
					inBounds = false;
					return true;
				}

				return false;
			}
		}
		void IPointerExit::RegisterToEvents(HUD::HUDRect * in_bounds)
		{
			bounds = in_bounds;

			GameEngine::manager.eventManager.AddIPointerEvent(EventManager::EXIT, this);
		}
	}
}