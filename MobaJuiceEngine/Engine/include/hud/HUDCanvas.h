#pragma once
#include <vector>
#include <memory>
#include <glm\glm.hpp>

using namespace std;
namespace Engine
{
	namespace HUD
	{
		class HUDCanvas {

		public:
			HUDCanvas();
			~HUDCanvas();

			//Start initialization of our Canvas
			virtual void Start();

			//Per frame tick of the engine
			virtual void Update();

			//Per frame draw call of the engine
			virtual void Draw(class HUD const * hud);

		protected:
			//Dimensions of the Canvas in Pixels
			float canvasWidth;
			float canvasHeight;

			//Position of our canvas. Bottom-left anchor
			float x;
			float y;

			//Array of our widget
			vector<unique_ptr<class HUDWidgets>> widgets;

			//Image of our canvas Background
			string canvasBackground;

		private:


		};
	}
}
