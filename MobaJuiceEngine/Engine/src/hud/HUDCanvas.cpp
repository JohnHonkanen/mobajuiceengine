#include "hud\HUDCanvas.h"
#include "hud\HUD.h"
#include "hud\HUDQuad.h"
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

		void HUDCanvas::Start()
		{
		}

		void HUDCanvas::Update()
		{
		}

		void HUDCanvas::Draw(HUD const * hud)
		{
			//Get our shader and use it
			OGLShader * shader = hud->GetShader();
			shader->Use();

			//Set up our model matrix
			glm::mat4 model;

			//To do: Move this to Start. Only needs to be calculated once
			model = translate(model, vec3(x, y, 0.0f));
			model = scale(model, vec3(canvasWidth, canvasWidth, 1.0f));

			//Send information to shader
			glUniformMatrix4fv(glGetUniformLocation(shader->program, "projection"), 1, GL_FALSE, glm::value_ptr(hud->GetProjection()));
			glUniformMatrix4fv(glGetUniformLocation(shader->program, "model"), 1, GL_FALSE, glm::value_ptr(model));

			//Sends texture information to the shader if we have set one
			if (canvasBackground != "") {
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, GameEngine::manager.textureManager.getTexture(canvasBackground));
				glUniform1i(glGetUniformLocation(shader->program, "texture0"), 0);
			}

			//Draw the quad
			hud->GetQuad()->Draw();

			//Go through widgets and draw them
		}
	}
}