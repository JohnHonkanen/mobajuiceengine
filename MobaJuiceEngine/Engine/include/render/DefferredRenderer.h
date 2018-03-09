#pragma once
#include "Renderer.h"
#include "FrameBuffer.h"
#include "GBuffer.h"
#include <memory>

namespace Engine
{
	class DefferredRenderer : public Renderer
	{
	public:
		void SetupFrameBuffers(unsigned int width, unsigned int height);
		void Render(std::vector<class GameObject*> objects);

	private:
		void ShadowPass(std::vector<class GameObject*> objects);
		void GeometryPass(std::vector<class GameObject*> objects);
		void LightPass(std::vector<class GameObject*> objects);
		void RenderScene();
		void DrawQuad();

		std::unique_ptr<FrameBuffer> shadowBuffer;
		std::unique_ptr<GBuffer> gBuffer;
		std::unique_ptr<FrameBuffer> lightBuffer;

		//Original Width and Height
		unsigned int oWidth, oHeight;
		unsigned int quadVAO;
	};
}
