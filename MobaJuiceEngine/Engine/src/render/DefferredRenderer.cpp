#include "render\DefferredRenderer.h"
#include "core\GameObject.h"
#include "core\GameEngine.h"
#include "components\MeshRenderer.h"
#include "GL\glew.h"

namespace Engine
{
	void DefferredRenderer::SetupFrameBuffers(unsigned int width, unsigned int height)
	{
		oWidth = width;
		oHeight = height;

		shadowBuffer = std::make_unique<FrameBuffer>(1024,1024, 1, true);
		gBuffer = std::make_unique<GBuffer>(width, height);

	}
	void DefferredRenderer::Render(std::vector<GameObject*> objects)
	{
		ShadowPass(objects);
		GeometryPass(objects);
		LightPass(objects);
		RenderScene();
	}

	void DefferredRenderer::ShadowPass(std::vector<GameObject*> objects)
	{
		glViewport(0, 0, shadowBuffer->GetWidth(), shadowBuffer->GetHeight());

		shadowBuffer->BindForWriting();

		glClear(GL_DEPTH_BUFFER_BIT);

		unsigned int shader = GameEngine::manager.shaderManager.GetShader("depthMap");

		glUseProgram(shader);

		//TODO Pass LightSpace things

		for (auto gameObject : objects)
		{
			if (gameObject->meshRenderer != nullptr)
			{
				gameObject->meshRenderer->SetShader(shader);
			}
			
			gameObject->Draw();
		}

		glViewport(0, 0, oWidth, oHeight); // Reset viewport to (Screen width and height)
	}
	void DefferredRenderer::GeometryPass(std::vector<class GameObject*> objects)
	{
		gBuffer->BindForWriting();
		glViewport(0, 0, oWidth, oHeight);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		unsigned int shader = GameEngine::manager.shaderManager.GetShader("geometry");

		glUseProgram(shader);

		for (auto gameObject : objects)
		{
			if (gameObject->meshRenderer != nullptr)
			{
				gameObject->meshRenderer->SetShader(shader);
			}

			gameObject->Draw();
		}
	}
}