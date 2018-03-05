#include "hud\HUDCanvas.h"
#include "hud\HUDQuad.h"
#include "hud\HUDWidget.h"
#include "render\OGLShader.h"
#include "core\GameEngine.h"

#include "GL\glew.h"
#include "glm\gtc\type_ptr.hpp"
#include "glm\gtc\matrix_transform.hpp"

namespace Engine 
{
	namespace HUD
	{
		HUDCanvas::HUDCanvas()
		{
		}

		HUDCanvas::~HUDCanvas()
		{
		}

		HUDCanvas * HUDCanvas::Create(HUD * hud, HUDRect rect, string background)
		{
			HUDCanvas * canvas = new HUDCanvas();
			canvas->rect = rect;
			canvas->canvasBackground = background;

			hud->AttachCanvasToHUD(canvas);

			return canvas;
		}

		void HUDCanvas::Start()
		{
			for (int i = 0; i < widgets.size(); i++) {
				widgets[i]->Start();
			}
		}

		void HUDCanvas::Update()
		{
			if (!active)
				return;

			for (int i = 0; i < widgets.size(); i++) {
				widgets[i]->Update();
			}
		}

		void HUDCanvas::Update(double dt)
		{
			if (!active)
				return;

			for (int i = 0; i < widgets.size(); i++) {
				widgets[i]->Update(dt);
			}
		}

		void HUDCanvas::Input()
		{
			if (!active)
				return;

			for (int i = 0; i < widgets.size(); i++) {
				widgets[i]->Input();
			}
		}

		void HUDCanvas::Draw(HUD const * hud)
		{
			if (!active)
				return;

			//Get our shader and use it
			OGLShader * shader = hud->GetShader();
			shader->Use();
			float resX, resY;

			resX = hud->GetWidth();
			resY = hud->GetHeight();

			//Sends texture information to the shader if we have set one
			if (canvasBackground != "") {
				
				//Set up our model matrix
				glm::mat4 model = mat4(1.0);

				//To do: Move this to Start. Only needs to be calculated once
				model = translate(model, vec3(rect.x + rect.width/2.0, resY - (rect.y + (rect.height/2.0f)), -1.0f));
				model = scale(model, vec3(rect.width/2.0f, rect.height/2.0f, 1.0f));


				//Send information to shader
				glUniformMatrix4fv(glGetUniformLocation(shader->program, "projection"), 1, GL_FALSE, glm::value_ptr(hud->GetProjection()));
				glUniformMatrix4fv(glGetUniformLocation(shader->program, "model"), 1, GL_FALSE, glm::value_ptr(model));

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, GameEngine::manager.textureManager.getTexture(canvasBackground));
				glUniform1i(glGetUniformLocation(shader->program, "texture0"), 0);

				//Draw the quad
				hud->GetQuad()->Draw();
			}

			HUDRect resRect = { rect.x , resY - rect.y, 0, 0};

			//Go through widgets and draw them
			for (int i = 0; i < widgets.size(); i++) {
				widgets[i]->Draw(hud, resRect);
			}
		}
		void HUDCanvas::SetRect(HUDRect rect)
		{
			HUDCanvas::rect = rect;
		}
		void HUDCanvas::SetBackground(string background)
		{
			canvasBackground = background;
		}
	}
}