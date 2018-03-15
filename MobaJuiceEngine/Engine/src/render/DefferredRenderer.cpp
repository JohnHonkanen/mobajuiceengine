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

		shadowBuffer = std::make_unique<FrameBuffer>(1024,1024, 1, true);
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

	}
	void DefferredRenderer::Render(std::vector<GameObject*> objects)
	{
		if (objects.empty())
		{
			return;
		}

		ShadowPass(objects);
		GeometryPass(objects);
		LightPass(objects);
		RenderScene();
		//TestDepthMap();
	}

	void DefferredRenderer::ShadowPass(std::vector<GameObject*> objects)
	{
		glViewport(0, 0, shadowBuffer->GetWidth(), shadowBuffer->GetHeight());

		shadowBuffer->BindForWriting();

		glClear(GL_DEPTH_BUFFER_BIT);

		unsigned int shader = GameEngine::manager.shaderManager.GetShader("depthMap");

		glUseProgram(shader);

		const Light * directional = LightManager::Get()->GetLights(DIRECTIONAL_LIGHT)[0];
		vec3 lightPosition = directional->transform->GetPosition();
		mat4 lightProjection = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, near_plane, far_plane);
		mat4 lightView = lookAt(lightPosition, vec3(0,0,0), vec3(0, 1, 0));
		lightSpaceMatrix = lightProjection * lightView;

		for (auto gameObject : objects)
		{
			gameObject->shader = shader;

			if (gameObject->meshRenderer != nullptr)
			{
				gameObject->meshRenderer->SetShader(shader);
				
			}

			vec3 objPosition = gameObject->transform->GetPosition();
			vec3 direction = normalize(objPosition - lightPosition);

			glUniformMatrix4fv(glGetUniformLocation(shader, "lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));

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
			gameObject->shader = shader;
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

		/*for (int i = GBuffer::POSITION; i != GBuffer::EMISSION; i++)
		{
			GBuffer::TEXTURE_TYPE type = static_cast<GBuffer::TEXTURE_TYPE>(i);
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, gBufferTextures[type]);
		}*/

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
		auto directionals = LightManager::Get()->GetLights(DIRECTIONAL_LIGHT);
		glUniform1i(glGetUniformLocation(shader, "numDirectionals"), directionals.size());
		PassLightsToShader(directionals, "directionalLights", shader);

		//Pass Point Light
		auto points = LightManager::Get()->GetLights(POINT_LIGHT);
		glUniform1i(glGetUniformLocation(shader, "numPoints"), points.size());
		PassLightsToShader(points, "pointLights", shader);

		//Pass Shadow Mapping
		glUniform1f(glGetUniformLocation(shader, "near_plane"), near_plane);
		glUniform1f(glGetUniformLocation(shader, "near_plane"), far_plane);
		glUniform1i(glGetUniformLocation(shader, "depthMap"), 4);
		glUniformMatrix4fv(glGetUniformLocation(shader, "lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));

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
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); //Write to default

		unsigned int shader = GameEngine::manager.shaderManager.GetShader("depthDebug");

		glUseProgram(shader);

		auto textures = shadowBuffer->GetTextures(); // 0 Texture, 1 Bloom texture

		glUniform1f(glGetUniformLocation(shader, "near_plane"), near_plane);
		glUniform1f(glGetUniformLocation(shader, "far_plane"), far_plane);

		//Set Uniform Location for texture0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textures[0]);

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
}