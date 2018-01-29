#pragma once
#include <vector>
#include <memory>
#include <glm\glm.hpp>
#include "hud\HUD.h"
#include "hud\HUDRect.h"
#include "hud\HUDElement.h"

using namespace std;
namespace Engine
{
	namespace HUD
	{
		class HUDCanvas : public HUDElement {

		public:
			HUDCanvas();
			~HUDCanvas();

			static HUDCanvas * Create(HUD * hud, HUDRect rect, string backGround);

			//Start initialization of our Canvas
			virtual void Start();

			//Per frame tick of the engine
			virtual void Update();

			//Per frame draw call of the engine
			virtual void Draw(HUD const * hud);

			void SetRect(struct HUDRect rect);

			void SetBackground(string background);

		protected:
			//Image of our canvas Background
			string canvasBackground;

		private:


		};
	}
}
