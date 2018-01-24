#pragma once
#include "hud\HUDRect.h"
namespace Engine
{
	namespace HUD
	{
		class HUDWidget
		{
		public:
			//Initialize our HUD in runtime
			virtual void Start() = 0;

			//Per frame tick of the engine
			virtual void Update() = 0;

			//Per frame draw call of the engine
			virtual void Draw() = 0;

			HUDRect GetRect() const;
			void EditRect(HUDRect rect);
			void EditRect(float x, float y, float width, float height);
		protected:
			HUDRect rect;
		};
	}
}
