#include "events\IPointerMouseDown.h"
#include "core\GameEngine.h"
namespace Engine
{
	namespace Events
	{
		bool IPointerMouseDown::Condition(glm::ivec2 position, EventData data)
		{
			bool pointerInBounds = Contains(position);

			if (pointerInBounds)
			{
				mouse0Down = data.mouseButton0;
				mouse1Down = data.mouseButton1;

				if (mouse0Down == 1 || mouse1Down == 1)
				{
					if (!buttonHeld)
					{
						buttonHeld = true;
						return true;
					}
					else {
						return false;
					}
					
				}
				buttonHeld = false;
				return false;

			}
			else{
				return false;
			}
		}
		void IPointerMouseDown::RegisterToEvents(HUD::HUDRect * in_bounds)
		{
			bounds = in_bounds;

			GameEngine::manager.eventManager.AddIPointerEvent(EventManager::MOUSE_DOWN, this);
		}
	}
}