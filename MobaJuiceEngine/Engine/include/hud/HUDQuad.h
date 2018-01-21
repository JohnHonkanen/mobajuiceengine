#pragma once

namespace Engine {
	namespace HUD {
		class HUDQuad
		{
		public:
			HUDQuad();
			~HUDQuad();
			//Get the VAO of our quad used for drawing
			unsigned int Get() const;
			//Draw our Quad
			void Draw();
		private:
			//Sets up our Quad for OpenGL drawing
			void SetupQuad();

			unsigned int vao;
			unsigned int vbo;

		};
	}
}
