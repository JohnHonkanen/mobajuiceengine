#pragma once

#include "hud\HUDWidget.h"
#include <glm\glm.hpp>

using namespace glm;

namespace Engine
{
	namespace HUD
	{
		class TextWidget : public HUDWidget
		{
		public:
			static unsigned int VAO, VBO;

			static TextWidget * Create(HUDElement * element, HUDRect rect, string text, string font, float scale, vec3 color);
			TextWidget();
			TextWidget(HUDRect rect, string text, string font, float scale, vec3 color);
			//Initialize our HUD in runtime
			void Start();

			//Per frame tick of the engine
			void Update();

			void Draw(class HUD const * hud, HUDRect parent);

			void DrawWidget(unsigned int shader);
		private:
			void SetupVAO();

			string text;
			string font;
			float scale;
			vec3 color;

		};
	}
}