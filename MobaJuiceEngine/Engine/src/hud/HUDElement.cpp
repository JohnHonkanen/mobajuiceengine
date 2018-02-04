#include "hud\HUDElement.h"
#include "hud\HUDWidget.h"

namespace Engine
{
	namespace HUD
	{
		HUDElement::HUDElement()
		{
		}
		HUDElement::HUDElement(bool isActive, bool canHandleEvent)
		{
			active = isActive;
		}
		void HUDElement::AttachWidget(HUDWidget * widget)
		{
			widget->AttachParentToRect(&rect);
			widgets.push_back(unique_ptr<HUDWidget>(widget));
		}
		void HUDElement::RemoveWidget(unsigned int widget)
		{
			widgets.erase(widgets.begin() + widget);
		}
		HUDRect HUDElement::GetRect() const
		{
			return rect;
		}
		void HUDElement::EditRect(HUDRect rect)
		{
			HUDElement::rect = rect;
		}
		void HUDElement::EditRect(float x, float y, float width, float height)
		{
			EditRect({ x, y, width, height });
		}

		void HUDElement::SetActive(bool active)
		{
			HUDElement::active = active;
		}
		bool HUDElement::IsActive() const
		{
			return active;
		}

		void HUDElement::ActivateEvents()
		{
			handleEvents = true;

			if (handleEvents)
			{
				//Register to handle Events
				IPointerEnter::RegisterToEvents(rect);

			}
		}

		void HUDElement::OnPointerEnter(EventData data)
		{
			printf("Entered HUD Element \n");
		}
		void HUDElement::AttachParentToRect(HUDRect *parent)
		{
			rect.parent = parent;
		}
	}
}