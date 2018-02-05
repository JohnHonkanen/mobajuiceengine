#include "events\EventManager.h"
#include "core\GameEngine.h"
#include "events\IPointerEnter.h"

namespace Engine
{
	namespace Events
	{
		void EventManager::Update()
		{
			LoopPointerEnterEvent();
		}
		void EventManager::LoopPointerEnterEvent()
		{
			//Mouse Position
			int mx, my;

			GameEngine::manager.inputManager.GetMousePos(mx, my);
			vec2 screen = GameEngine::screenSize;
			my = screen.y - my;

			//printf("mouseX: %i, mouseY: %i \n", mx, my);
			for (auto &pointerEnterEvent : pointerEnterObject) {
				if (pointerEnterEvent->Condition(ivec2(mx, my)))
				{
					pointerEnterEvent->OnPointerEnter(data);
				}
			}
		}
		void EventManager::AddPointerEnterEvent(IPointerEnter * object)
		{
			pointerEnterObject.push_back(object);
		}
	}
}