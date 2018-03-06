#pragma once
#include "hud\HUDWidget.h"
#include <string>
namespace Engine
{
	namespace HUD
	{
		class WHUDContainer : public HUDWidget {
		public:

			static WHUDContainer * Create(HUDElement * element, HUDRect rect, std::string backGround, bool callEvents);
			WHUDContainer(bool callEvents, HUDRect rect);
			//Initialize our HUD in runtime
			void Start();

			//Per frame tick of the engine
			void Update();

			void Update(double dt);

			void DrawWidget(unsigned int shader);

			void ChangeImage(std::string image);
		private:
			//Image of our canvas Background
			std::string background;
		};
	}
}