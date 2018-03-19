#pragma once
#include "Renderer.h"
#include "FrameBuffer.h"
#include "GBuffer.h"
#include <memory>
#include "components\Light.h"

#define NUM_CASCADES 3
namespace Engine
{
	class DefferredRenderer : public Renderer
	{
	public:
		enum BUFFERS
		{
			SHADOW,
			GBUFFER,
			LIGHTBUFFER
		};
		void SetupFrameBuffers(unsigned int width, unsigned int height);
		void Render(std::vector<class GameObject*> objects);

		void ReadBuffer(BUFFERS type);
	private:
		void ShadowPass(std::vector<class GameObject*> objects);
		void GeometryPass(std::vector<class GameObject*> objects);
		void LightPass(std::vector<class GameObject*> objects);
		void RenderScene();
		void TestDepthMap();
		void DrawQuad();

		/*Utility Functions*/
		void PassLightsToShader(vector<Light*> lights, std::string locString, unsigned int shader);
		void CalcShadowMapOrthoProj();

		std::unique_ptr<FrameBuffer> shadowBuffer;
		std::unique_ptr<GBuffer> gBuffer;
		std::unique_ptr<FrameBuffer> lightBuffer;

		mat4 lightSpaceMatrix;
		float shadowMapCascades[4];
		mat4 shadowOrthoProj[NUM_CASCADES];
		float clippingPlanes[6];

		//Original Width and Height
		unsigned int oWidth, oHeight;
		unsigned int quadVAO;

		//For Shadows
		float near_plane = 1.0f;
		float far_plane = 100.0f;
	};
}
