#include "events\EventManager.h"
#include "core\GameEngine.h"
#include "events\IPointer.h"
#include "events\IPointerEnter.h"
#include "events\IPointerExit.h"
#include "events\IPointerMouseDown.h"

namespace Engine
{
	namespace Events
	{
		void EventManager::Update()
		{
			UpdateEventData();
			LoopIPointerEvents();
		}
		void EventManager::UpdateEventData()
		{
			data.mouseButton0 = GameEngine::manager.inputManager.GetKey("mouse0");
			data.mouseButton1 = GameEngine::manager.inputManager.GetKey("mouse1");
		}
		void EventManager::LoopIPointerEvents()
		{
			//Mouse Position
			int mx, my;

			GameEngine::manager.inputManager.GetMousePos(mx, my);
			vec2 screen = GameEngine::screenSize;
			my = screen.y - my;

			//Pointer Enter event
			for (auto &pointerEnterEvent : pointerEnterObject) {
				if (pointerEnterEvent->Condition(ivec2(mx, my), data))
				{
					pointerEnterEvent->OnPointerEnter(data);
				}
			}

			//Pointer Exit event
			for (auto &pointerExitEvent : pointerExitObject) {
				if (pointerExitEvent->Condition(ivec2(mx, my), data))
				{
					pointerExitEvent->OnPointerExit(data);
				}
			}

			//Pointer Down event
			for (auto &pointerDownEvent : pointerDownObject) {
				if (pointerDownEvent->Condition(ivec2(mx, my), data))
				{
					pointerDownEvent->OnPointerMouseDown(data);
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
				pointerExitObject.push_back(dynamic_cast<IPointerExit*>(eventObject));
				break;
			case Engine::Events::EventManager::MOUSE_DOWN:
				pointerDownObject.push_back(dynamic_cast<IPointerMouseDown*>(eventObject));
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