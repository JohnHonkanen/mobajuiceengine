#include "events\EventManager.h"
#include "core\GameEngine.h"
#include "events\IPointer.h"
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

		void EventManager::AddIPointerEvent(IPOINTER_EVENT type, IPointer *eventObject)
		{
			switch (type)
			{
			case Engine::Events::EventManager::ENTER:
				pointerEnterObject.push_back(dynamic_cast<IPointerEnter*>(eventObject));
				break;
			case Engine::Events::EventManager::EXIT:
				break;
			case Engine::Events::EventManager::MOUSE_DOWN:
				break;
			case Engine::Events::EventManager::MOUSE_UP:
				break;
			case Engine::Events::EventManager::ON_DRAG:
				break;
			default:
				break;
			}
		}
	}
}