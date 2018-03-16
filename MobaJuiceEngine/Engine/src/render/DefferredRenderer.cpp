#include "render\DefferredRenderer.h"
#include "core\GameObject.h"
#include "core\GameEngine.h"
#include "components\MeshRenderer.h"
#include "components\Camera.h"
#include "GL\glew.h"
#include "render\LightManager.h"
namespace Engine
{
	void DefferredRenderer::SetupFrameBuffers(unsigned int width, unsigned int height)
	{
		oWidth = width;
		oHeight = height;

		shadowBuffer = std::make_unique<FrameBuffer>(1024,1024, NUM_CASCADES, true);
		gBuffer = std::make_unique<GBuffer>(width, height);
		lightBuffer = std::make_unique<FrameBuffer>(width, height, 2);

		shadowBuffer->Init();
		gBuffer->Init();
		lightBuffer->Init();

		unsigned int light = GameEngine::manager.shaderManager.GetShader("light");
		glUniform1i(glGetUniformLocation(light, "gPosition"), 0);
		glUniform1i(glGetUniformLocation(light, "gNormal"), 1);
		glUniform1i(glGetUniformLocation(light, "gAlbedoSpec"), 2);
		glUniform1i(glGetUniformLocation(light, "gEmission"), 3);

		Camera *camera = Camera::mainCamera;
		shadowMapCascades[0] = camera->GetNear();
		shadowMapCascades[1] = 100;
		shadowMapCascades[2] = 350;
		shadowMapCascades[3] = camera->GetFar();

		unsigned int lightPass = GameEngine::manager.shaderManager.GetShader("light");

		glUseProgram(lightPass);

		for (unsigned int i = 0; i < NUM_CASCADES; i++)
		{
			vec4 vView = -vec4(0.0f, 0.0f, shadowMapCascades[i + 1], 1.0f);
			vec4 vClip = camera->GetProjectionMatrix() * vView;
			glUniform1f(glGetUniformLocation(lightPass, ("CascadeEndClipSpace[" + to_string(i) + "]").c_str()), vClip.z);
		}


		glUseProgram(0);


	}
	void DefferredRenderer::Render(std::vector<GameObject*> objects)
	{
		if (objects.empty())
		{
			return;
		}

		glDisable(GL_BLEND);

		ShadowPass(objects);
		GeometryPass(objects);
		LightPass(objects);
		//RenderScene();
		TestDepthMap();

		glEnable(GL_BLEND);
	}

	void DefferredRenderer::ShadowPass(std::vector<GameObject*> objects)
	{
		CalcShadowMapOrthoProj();

		//glViewport(0, 0, shadowBuffer->GetWidth(), shadowBuffer->GetHeight());

		unsigned int shader = GameEngine::manager.shaderManager.GetShader("depthMap");

		glUseProgram(shader);
		

		for (unsigned int i = 0; i < NUM_CASCADES; i++)
		{
			shadowBuffer->BindForWriting(i);
			glClear(GL_DEPTH_BUFFER_BIT);
			
			for (auto gameObject : objects)
			{
				glUniformMatrix4fv(glGetUniformLocation(shader, "lightSpaceMatrix"), 1, GL_TRUE, glm::value_ptr(shadowOrthoProj[i]));

				gameObject->shader = shader;
				gameObject->shaderName = "depthMap";

				if (gameObject->meshRenderer != nullptr)
				{
					gameObject->meshRenderer->SetShader(shader);

				}

				gameObject->Draw();
			}

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
			gameObject->shader = shader;
			gameObject->shaderName = "geometry";
			if (gameObject->meshRenderer != nullptr)
			{
  				gameObject->meshRenderer->SetShader(shader);
				
			}

			gameObject->Draw();
		}
	}
	void DefferredRenderer::LightPass(std::vector<class GameObject*> objects)
	{
		lightBuffer->BindForWriting();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		unsigned int shader = GameEngine::manager.shaderManager.GetShader("light");

		glUseProgram(shader);

		auto gBufferTextures = gBuffer->GetTextures(); //Map (Gbuffer)

		auto shadowTextures = shadowBuffer->GetTextures(); //vector (FrameBuffer)

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, gBufferTextures[GBuffer::POSITION]);
		glUniform1i(glGetUniformLocation(shader, "gPosition"), 0);


		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, gBufferTextures[GBuffer::NORMAL]);
		glUniform1i(glGetUniformLocation(shader, "gNormal"), 1);


		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, gBufferTextures[GBuffer::ALBEDOSPEC]);
		glUniform1i(glGetUniformLocation(shader, "gAlbedoSpec"), 2);
		

		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, gBufferTextures[GBuffer::EMISSION]);
		glUniform1i(glGetUniformLocation(shader, "gEmission"), 3);

		glActiveTexture(GL_TEXTURE4);

		//Get Camera Position and Direction
		Camera * camera = Camera::mainCamera;

		glm::vec3 cameraPosition = camera->transform->GetPosition();
		glm::vec3 cameraDirection = camera->transform->Front();

		//Get View Position
		glm::vec3 viewPosition = camera->GetViewMatrix()[3];
		glUniform3f(glGetUniformLocation(shader, "viewPosition"), viewPosition.x,viewPosition.y, viewPosition.z);

		//Pass Directional Light
		auto directionalLight = LightManager::Get()->GetLights(DIRECTIONAL_LIGHT)[0];


		auto prop = directionalLight->GetProperties();
		vec3 position = -normalize(directionalLight->transform->GetPosition()); //directionalLight->transform->GetPosition();

		printf("dir: %f , %f, %f \n", position.x, position.y, position.z);
		string uniformLoc = "directionalLight";
		glUniform3f(glGetUniformLocation(shader, (uniformLoc + ".position").c_str()),
			position.x, position.y, position.z
		);

		glUniform3f(glGetUniformLocation(shader, (uniformLoc + ".ambient").c_str()),
			prop.ambient.x, prop.ambient.y, prop.ambient.z
		);
		glUniform3f(glGetUniformLocation(shader, (uniformLoc + ".diffuse").c_str()),
			prop.diffuse.x, prop.diffuse.y, prop.diffuse.z
		);
		glUniform3f(glGetUniformLocation(shader, (uniformLoc + ".specular").c_str()),
			prop.specular.x, prop.specular.y, prop.specular.z
		);

		glUniform1f(glGetUniformLocation(shader, (uniformLoc + ".constant").c_str()),
			prop.constant
		);

		glUniform1f(glGetUniformLocation(shader, (uniformLoc + ".linear").c_str()),
			prop.linear
		);

		glUniform1f(glGetUniformLocation(shader, (uniformLoc + ".quadratic").c_str()),
			prop.quadratic
		);

		//Pass Point Light
		auto points = LightManager::Get()->GetLights(POINT_LIGHT);
		glUniform1i(glGetUniformLocation(shader, "numPoints"), points.size());
		PassLightsToShader(points, "pointLights", shader);

		//Pass Shadow Mapping
		glUniform1f(glGetUniformLocation(shader, "near_plane"), near_plane);
		glUniform1f(glGetUniformLocation(shader, "near_plane"), far_plane);


		for (unsigned int i = 0; i < NUM_CASCADES; i++)
		{
			glActiveTexture(GL_TEXTURE4 + i);
			glBindTexture(GL_TEXTURE_2D, shadowTextures[i]);
			glUniform1i(glGetUniformLocation(shader, ("shadowMaps[" + to_string(i) + "]").c_str()), 4 + i);

			glUniformMatrix4fv(glGetUniformLocation(shader, ("lightSpaceMatrix[" + to_string(i) + "]").c_str()), 1, GL_TRUE, glm::value_ptr(shadowOrthoProj[i]));
		}
		

		//RenderQuad
		DrawQuad();

	}
	void DefferredRenderer::RenderScene()
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); //Write to default

		unsigned int shader = GameEngine::manager.shaderManager.GetShader("default");

		glUseProgram(shader);

		auto textures = lightBuffer->GetTextures(); // 0 Texture, 1 Bloom texture


		//Set Uniform Location for texture0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textures[0]);

		DrawQuad();
	}
	void DefferredRenderer::TestDepthMap()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); //Write to default

		unsigned int shader = GameEngine::manager.shaderManager.GetShader("depthDebug");

		glUseProgram(shader);

		auto textures = shadowBuffer->GetTextures(); // 0 Texture, 1 Bloom texture
		Camera *c = Camera::mainCamera;
		glUniform1f(glGetUniformLocation(shader, "near_plane"), c->GetNear());
		glUniform1f(glGetUniformLocation(shader, "far_plane"), c->GetFar());

		//Set Uniform Location for texture0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glUniform1i(glGetUniformLocation(shader, "depthMap"), 0);

		DrawQuad();
	}
	void DefferredRenderer::DrawQuad()
	{
		unsigned int quadVBO;
		if (quadVAO == 0)
		{
			float quadVertices[] = {
				// positions        // texture Coords
				-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
				-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
				1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
				1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
			};
			// setup plane VAO
			glGenVertexArrays(1, &quadVAO);
			glGenBuffers(1, &quadVBO);
			glBindVertexArray(quadVAO);
			glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		}
		glBindVertexArray(quadVAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);
	}
	void DefferredRenderer::PassLightsToShader(vector<Light*> lights, std::string locString,unsigned int shader)
	{
		for (int i = 0; i < lights.size(); i++)
		{
			auto prop = lights[i]->GetProperties();
			vec3 position = lights[i]->transform->GetPosition();
			string uniformLoc = locString + "[" + std::to_string(i) + "]";
			glUniform3f(glGetUniformLocation(shader, (uniformLoc + ".position").c_str()),
				position.x, position.y, position.z
			);

			glUniform3f(glGetUniformLocation(shader, (uniformLoc + ".ambient").c_str()),
				prop.ambient.x, prop.ambient.y, prop.ambient.z
			);
			glUniform3f(glGetUniformLocation(shader, (uniformLoc + ".diffuse").c_str()),
				prop.diffuse.x, prop.diffuse.y, prop.diffuse.z
			);
			glUniform3f(glGetUniformLocation(shader, (uniformLoc + ".specular").c_str()),
				prop.specular.x, prop.specular.y, prop.specular.z
			);

			glUniform1f(glGetUniformLocation(shader, (uniformLoc + ".constant").c_str()),
				prop.constant
			);

			glUniform1f(glGetUniformLocation(shader, (uniformLoc + ".linear").c_str()),
				prop.linear
			);

			glUniform1f(glGetUniformLocation(shader, (uniformLoc + ".quadratic").c_str()),
				prop.quadratic
			);
		}
	}

	#define NUM_FRUSTRUM_CORNERS 8

	void DefferredRenderer::CalcShadowMapOrthoProj()
	{
		//Get the inverse of the view transform
		Camera * camera = Camera::mainCamera;
		mat4 view = camera->GetViewMatrix();
		mat4 invView = inverse(view);

		printf("Camera Pos : %f, %f, %f\n", camera->transform->GetPosition().x, camera->transform->GetPosition().y, camera->transform->GetPosition().z);
		//Get the lightspace transform
		const Light * directional = LightManager::Get()->GetLights(DIRECTIONAL_LIGHT)[0];
		vec3 lightDir = -normalize(camera->transform->GetPosition());
		mat4 lightView = lookAt(camera->transform->GetPosition(), vec3(0), vec3(0,1,0));

		float aspectRatio = 1;//camera->GetAspectRatio();
		float fov = camera->GetFOV();

		float tanHalfHFOV = tanf(radians(fov / 2.0f));
		float tanHalfVFOV = tanf(radians(((fov * aspectRatio) / 2.0f)));

		printf("ar %f tanHalfHFOV %f tanHalfVFOV %f\n", aspectRatio, tanHalfHFOV, tanHalfVFOV);
		for (unsigned int i = 0; i < NUM_CASCADES; i++)
		{
			float xn = shadowMapCascades[i] * tanHalfHFOV;
			float xf = shadowMapCascades[i + 1] * tanHalfHFOV;
			float yn = shadowMapCascades[i] * tanHalfVFOV;
			float yf = shadowMapCascades[i + 1] * tanHalfVFOV;

			printf("xn %f xf %f\n", xn, xf);
			printf("yn %f yf %f\n", yn, yf);

			vec4 frustumCorners[NUM_FRUSTRUM_CORNERS] = {
				//near face
				vec4(xn, yn, shadowMapCascades[i], 1.0),
				vec4(-xn, yn, shadowMapCascades[i], 1.0),
				vec4(xn, -yn, shadowMapCascades[i], 1.0),
				vec4(-xn, -yn, shadowMapCascades[i], 1.0),

				//far face
				vec4(xf, yf, shadowMapCascades[i + 1], 1.0),
				vec4(-xf, yf, shadowMapCascades[i + 1], 1.0),
				vec4(xf, -yf, shadowMapCascades[i + 1], 1.0),
				vec4(-xf, -yf, shadowMapCascades[i + 1], 1.0)
			};

			vec4 frustumCornersL[NUM_FRUSTRUM_CORNERS];
			vec4 frustumCornersCL[NUM_FRUSTRUM_CORNERS];

			float minX = std::numeric_limits<float>::max();
			float maxX = std::numeric_limits<float>::min();
			float minY = std::numeric_limits<float>::max();
			float maxY = std::numeric_limits<float>::min();
			float minZ = std::numeric_limits<float>::max();
			float maxZ = std::numeric_limits<float>::min();

			float minCZ = std::numeric_limits<float>::max();
			float maxCZ = std::numeric_limits<float>::min();

			for (unsigned int j = 0; j < NUM_FRUSTRUM_CORNERS; j++)
			{
				vec4 vW = invView * frustumCorners[j];
				frustumCornersL[j] = vW;
				frustumCornersCL[j] = vW * lightView;

				minX = min(minX, frustumCornersL[j].x);
				maxX = max(maxX, frustumCornersL[j].x);

				minY = min(minY, frustumCornersL[j].y);
				maxY = max(maxY, frustumCornersL[j].y);

				minZ = min(minZ, frustumCornersL[j].z);
				maxZ = max(maxZ, frustumCornersL[j].z);

				minCZ = min(minCZ, frustumCornersCL[j].z);
				maxCZ = max(maxCZ, frustumCornersCL[j].z);
			}

			clippingPlanes[i * 2] = -25.0f;
			clippingPlanes[i * 2 + 1] = 50.0f;

			printf("BB %i: %f %f %f %f %f %f\n", i, minX, maxX, minY, maxY, minZ, maxZ);

			shadowOrthoProj[i] = camera->GetProjectionMatrix() * view;
		}
	}
}