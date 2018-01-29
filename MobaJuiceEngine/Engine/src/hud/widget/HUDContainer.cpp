#include "hud\widgets\HUDContainer.h"
#include "core\GameEngine.h"
#include <GL\glew.h>

namespace Engine
{
	namespace HUD
	{
		WHUDContainer * WHUDContainer::Create(HUDElement * element, HUDRect rect, std::string background)
		{
			WHUDContainer * container = new WHUDContainer();
			container->rect = rect;
			container->background = background;
			element->AttachWidget(container);

			return container;
		}
		void WHUDContainer::Start()
		{
		}
		void WHUDContainer::Update()
		{
		}
		void WHUDContainer::DrawWidget(unsigned int shader)
		{
			if (background != "") {
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, GameEngine::manager.textureManager.getTexture(background));
				glUniform1i(glGetUniformLocation(shader, "texture0"), 0);
			}
		}
	}
}