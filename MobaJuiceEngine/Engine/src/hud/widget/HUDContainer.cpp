#include "hud\widgets\HUDContainer.h"
#include "core\GameEngine.h"
#include <GL\glew.h>

namespace Engine
{
	namespace HUD
	{
		WHUDContainer * WHUDContainer::Create(HUDElement * element, HUDRect rect, std::string background, bool callEvents)
		{
			WHUDContainer * container = new WHUDContainer(callEvents, rect);
			container->background = background;
			element->AttachWidget(container);

			return container;
		}
		WHUDContainer::WHUDContainer(bool callEvents, HUDRect rect)
		{
			HUDElement::rect = rect;
		}
		void WHUDContainer::Start()
		{
			StartChildWidgets();
		}
		void WHUDContainer::Update()
		{
			if (!active)
				return;

			UpdateChildWidgets();
		}
		void WHUDContainer::Update(double dt)
		{
			if (!active)
				return;

			UpdateChildWidgets(dt);
		}
		void WHUDContainer::DrawWidget(unsigned int shader)
		{
			if (background != "") {
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, GameEngine::manager.textureManager.getTexture(background));
				glUniform1i(glGetUniformLocation(shader, "texture0"), 0);
			}
		}
		void WHUDContainer::ChangeImage(std::string image)
		{
			background = image;
		}
	}
}