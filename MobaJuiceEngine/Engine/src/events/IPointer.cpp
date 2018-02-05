#include "events\IPointer.h"
#include "hud\HUDRect.h"
namespace Engine
{
	namespace Events
	{
		bool IPointer::Contains(glm::ivec2 position)
		{
			return bounds->Contains(position.x, position.y);
		}
	}
}