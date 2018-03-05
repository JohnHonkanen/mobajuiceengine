#pragma once
#include <memory>
#include <glm\glm.hpp>
using namespace std;

namespace Engine {
	class OGLShader;
	class Scene;
	namespace HUD {
		class HUD {
		public:
			//ctor and dtor
			HUD();
			~HUD();

			//Create function for our HUD
			static HUD * Create(Scene * scene, float width, float height);
			//Initialize our HUD in runtime
			virtual void Start();

			//Per frame tick of the engine
			virtual void Update();
			virtual void Update(double dt);

			virtual void Input();

			//Per frame draw call of the engine
			virtual void Draw();
			
			/** Attach the canvas to our HUD
			*	@param canvas	Canvas that we want to add our our HUD
			*/
			void AttachCanvasToHUD(class HUDCanvas * canvas);

			/** Set the resolution of our hud
			*	@param x	width of our resolution size
			*	@param y	height of our resolution size
			*/
			void SetResolution(float const x, float const y);

			/** Get the size of the hud resolution*/
			float GetWidth() const;
			float GetHeight() const;

			glm::mat4 GetProjection() const;

			OGLShader * GetShader()  const;

			class HUDQuad * GetQuad() const;
		protected:

			//Canvas component used to specify screen size
			unique_ptr<class HUDCanvas> canvas;

			//Size of our HUD
			float resolutionWidth, resolutionHeight;

			//Projection of our HUD
			glm::mat4 projection;

			//Check if we can update
			bool canTick;

			//Default Shaders used to draw the HUD
			const char * defaultVertexShader;
			const char * defaultFramentShader;

			//Shader Used to draw our GUI
			OGLShader * shader;

			class HUDQuad * quad;

		private:
			//Calculate the projection of our HUD
			void CalculateProjection();

		};
	}
}
