#include "hud\HUD.h"
#include "hud\HUDCanvas.h"
#include "hud\HUDQuad.h"
#include "core\GameEngine.h"
#include "core\Scene.h"
#include "render\OGLShader.h"

#include <glm\gtc\matrix_transform.hpp>

namespace Engine
{
	namespace HUD
	{
		HUD::HUD() 
		{
			quad = new HUDQuad();
			canTick = true;
			defaultVertexShader = "Assets/Shaders/defaultHUD.vert";
			defaultFramentShader = "Assets/Shaders/defaultHUD.frag";
		}

		HUD::~HUD() 
		{
			delete quad;
		}

		HUD * HUD::Create(Engine::Scene  *scene, float width, float height)
		{
			HUD *hud = new HUD();
			hud->resolutionWidth = width;
			hud->resolutionHeight = height;
			scene->AttachHUD(hud);
			return hud;
		}

		void HUD::Start()
		{
			quad->SetupQuad();
			//Create and get our shader from the shader manager
			shader = GameEngine::manager.shaderManager.CreateShader("defaultHUDShader", defaultVertexShader, defaultFramentShader);

			CalculateProjection();

			if (canvas) {
				canvas->Start();
			}
		}

		void HUD::Update() 
		{
			//If we can tick and canvas exist
			if (canTick && canvas) {
				canvas->Update();
			}
		}


		void HUD::Draw() 
		{
			glDisable(GL_DEPTH_TEST);
			//If canvas exist
			if (canvas) {
				canvas->Draw(this);
			}
			glEnable(GL_DEPTH_TEST);
		}

		//Attach a canvas to our HUD
		void HUD::AttachCanvasToHUD(HUDCanvas * canvas)
		{
			HUD::canvas = unique_ptr<HUDCanvas>(canvas);
		}

		/** Set the resolution of our hud */
		void HUD::SetResolution(float const x, float const y)
		{
			resolutionWidth = x;
			resolutionHeight = y;
		}

		float HUD::GetWidth() const
		{
			return resolutionWidth;
		}

		float HUD::GetHeight() const
		{
			return resolutionHeight;
		}

		glm::mat4 HUD::GetProjection() const
		{
			return projection;
		}

		OGLShader * HUD::GetShader() const
		{
			return shader;
		}

		HUDQuad * HUD::GetQuad() const
		{
			return quad;
		}

		//Calculates the projection of our HUD
		void HUD::CalculateProjection()
		{
			projection = glm::ortho(0.0f, resolutionWidth, 0.0f, resolutionHeight, 0.1f, 10.0f);
		}
	}
}