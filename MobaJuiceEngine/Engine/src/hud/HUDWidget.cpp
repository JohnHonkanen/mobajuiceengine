#include "hud\HUDWidget.h"
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
		void HUDWidget::StartChildWidgets()
		{
			for (int i = 0; i < widgets.size(); i++) {
				widgets[i]->Start();
			}
		}
		void HUDWidget::UpdateChildWidgets()
		{
			for (int i = 0; i < widgets.size(); i++) {
				widgets[i]->Update();
			}
		}
		void HUDWidget::Draw(HUD const * hud, HUDRect parent)
		{
			if (!active)
				return;

			//Get our shader and use it
			OGLShader * shader = hud->GetShader();
			shader->Use();

			//Set up our model matrix
			glm::mat4 model;

			//To do: Move this to Start. Only needs to be calculated once
			vec3 finalPos = vec3(parent.x + rect.x + rect.width / 2.0f,
				parent.y - (rect.y + rect.height / 2.0f),
				-1.0f);

			model = translate(model, 
				finalPos);
			model = scale(model, vec3(rect.width/2.0f, rect.height/2.0f, 1.0f));


			//Send information to shader
			glUniformMatrix4fv(glGetUniformLocation(shader->program, "projection"), 1, GL_FALSE, glm::value_ptr(hud->GetProjection()));
			glUniformMatrix4fv(glGetUniformLocation(shader->program, "model"), 1, GL_FALSE, glm::value_ptr(model));

			DrawWidget(shader->program);

			//Draw the quad
			hud->GetQuad()->Draw();

			HUDRect fRect = {rect.x, -rect.y, rect.width, rect.height};
			//Go through widgets and draw them
			for (int i = 0; i < widgets.size(); i++) {
				widgets[i]->Draw(hud, parent + fRect);
			}
			
		}
	}
}