#pragma once
#include "hud\HUDRect.h"
#include "hud\HUDElement.h"
#include <vector>

namespace Engine
{
	namespace HUD
	{
		class HUDWidget : public HUDElement
		{
		public:
			//Initialize our HUD in runtime
			virtual void Start() = 0;
			void StartChildWidgets();
			void UpdateChildWidgets();
			void UpdateChildWidgets(double dt);

			//Per frame tick of the engine
			virtual void Update() = 0;
			virtual void Update(double dt) {};

			virtual void Input() {};

			//Per frame draw call of the engine
			void virtual Draw(class HUD const * hud, HUDRect parent);

			//Widget-only draw implementation
			virtual void DrawWidget(unsigned int shader) = 0;

		};
	}
}
