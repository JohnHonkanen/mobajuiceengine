#pragma once
#include "Renderer.h"
#include "FrameBuffer.h"
#include "GBuffer.h"
#include <memory>
#include "components\Light.h"

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
		void TestDepthMap();
		void DrawQuad();

		/*Utility Functions*/
		void PassLightsToShader(vector<Light*> lights, std::string locString, unsigned int shader);

		std::unique_ptr<FrameBuffer> shadowBuffer;
		std::unique_ptr<GBuffer> gBuffer;
		std::unique_ptr<FrameBuffer> lightBuffer;

		mat4 lightSpaceMatrix;

		//Original Width and Height
		unsigned int oWidth, oHeight;
		unsigned int quadVAO;

		//For Shadows
		float near_plane = 1.0f;
		float far_plane = 25.0f;
	};
}
