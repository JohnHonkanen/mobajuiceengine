#include "events\IPointerEnter.h"
#include "core\GameEngine.h"

namespace Engine
{
	namespace Events
	{
		void IPointerEnter::RegisterToEvents(Engine::HUD::HUDRect in_bounds)
		{
			bounds = in_bounds;

			GameEngine::manager.eventManager.AddPointerEnterEvent(this);
		}
	}
}