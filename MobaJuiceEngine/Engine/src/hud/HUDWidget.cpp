#include "hud\HUDWidget.h"

namespace Engine
{
	namespace HUD
	{
		HUDRect HUDWidget::GetRect() const
		{
			return rect;
		}
		void HUDWidget::EditRect(HUDRect rect)
		{
			HUDWidget::rect = rect;
		}
		void HUDWidget::EditRect(float x, float y, float width, float height)
		{
			EditRect({x, y, width, height});
		}
	}
}