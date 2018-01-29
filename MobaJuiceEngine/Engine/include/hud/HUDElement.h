#pragma once
#include "hud\HUDRect.h"
#include <vector>
#include <memory>

using namespace std;
namespace Engine
{
	namespace HUD
	{
		class HUDElement
		{
		public:
			//Attach a widget to the element
			void AttachWidget(class HUDWidget * widget);
			//Removes the widget from the element
			void RemoveWidget(unsigned int widget);
			HUDRect GetRect() const;
			//Edit the rect element
			void EditRect(HUDRect rect);
			void EditRect(float x, float y, float width, float height);

			//Set active boolean
			void SetActive(bool active);
			//Get the active boolean
			bool IsActive() const;
		protected:
			bool active = true;
			//Array of attached widgets
			std::vector<unique_ptr<class HUDWidget>> widgets;
			HUDRect rect;
		};
	}
}