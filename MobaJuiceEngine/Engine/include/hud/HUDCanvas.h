#pragma once
#include <vector>
#include <memory>
#include <glm\glm.hpp>
#include "hud\HUD.h"
#include "hud\HUDRect.h"

using namespace std;
namespace Engine
{
	namespace HUD
	{
		class HUDCanvas {

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
			struct HUDRect rect;

			//Array of our widget
			vector<unique_ptr<class HUDWidget>> widgets;

			//Image of our canvas Background
			string canvasBackground;

		private:


		};
	}
}
