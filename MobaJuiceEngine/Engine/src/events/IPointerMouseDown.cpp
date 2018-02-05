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
				if (!mouse0Down || !mouse1Down)
				{
					mouse0Down = data.mouseButton0;
					mouse1Down = data.mouseButton1;
					return true;
				}

				return false;

			}
			else{

				if (mouse0Down || mouse1Down)
				{
					mouse0Down = data.mouseButton0;
					mouse1Down = data.mouseButton1;
				}
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