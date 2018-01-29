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
		void HUDWidget::Draw(HUD const * hud, HUDRect parent)
		{
			//Get our shader and use it
			OGLShader * shader = hud->GetShader();
			shader->Use();

			//Set up our model matrix
			glm::mat4 model;

			//To do: Move this to Start. Only needs to be calculated once
			model = translate(model, 
				vec3(parent.x + rect.x + rect.width/2.0f, 
				parent.y - (rect.y + rect.height/2.0f), 
					-1.0f));
			model = scale(model, vec3(rect.width/2.0f, rect.height/2.0f, 1.0f));


			//Send information to shader
			glUniformMatrix4fv(glGetUniformLocation(shader->program, "projection"), 1, GL_FALSE, glm::value_ptr(hud->GetProjection()));
			glUniformMatrix4fv(glGetUniformLocation(shader->program, "model"), 1, GL_FALSE, glm::value_ptr(model));

			DrawWidget(shader->program);

			//Draw the quad
			hud->GetQuad()->Draw();


			//Go through widgets and draw them
			for (int i = 0; i < widgets.size(); i++) {
				widgets[i]->Draw(hud, parent + rect);
			}
			
		}
	}
}