#include "render\DefferredRenderer.h"
#include "core\GameObject.h"
#include "core\GameEngine.h"
#include "components\MeshRenderer.h"
#include "components\Camera.h"
#include "GL\glew.h"
#include "render\LightManager.h"
#include <glm\gtc\matrix_inverse.hpp>
#include <glm\gtx\quaternion.hpp>
#include <glm\gtx\matrix_decompose.hpp>
namespace Engine
{
	void DefferredRenderer::SetupFrameBuffers(unsigned int width, unsigned int height)
	{
		oWidth = width;
		oHeight = height;

		shadowBuffer = std::make_unique<FrameBuffer>(2048,2048, NUM_CASCADES, true);
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
		shadowMapCascades[1] = camera->GetFar() * 0.3f;
		shadowMapCascades[2] = camera->GetFar() * 0.7f;
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
		RenderScene();
		//TestDepthMap();

		glEnable(GL_BLEND);
	}

	void DefferredRenderer::ReadBuffer(BUFFERS type)
	{
		switch (type)
		{
		case Engine::DefferredRenderer::SHADOW:
			shadowBuffer->BindForReading();
			break;
		case Engine::DefferredRenderer::GBUFFER:
			gBuffer->BindForReading();
			break;
		case Engine::DefferredRenderer::LIGHTBUFFER:
			lightBuffer->BindForReading();
			break;
		default:
			break;
		}
	}

	void DefferredRenderer::ShadowPass(std::vector<GameObject*> objects)
	{
		CalcShadowMapOrthoProj();
		glCullFace(GL_FRONT);

		glViewport(0, 0, shadowBuffer->GetWidth(), shadowBuffer->GetHeight());

		unsigned int shader = GameEngine::manager.shaderManager.GetShader("depthMap");

		glUseProgram(shader);
		

		for (unsigned int i = 0; i < NUM_CASCADES; i++)
		{
			shadowBuffer->BindForWriting(i);
			glClear(GL_DEPTH_BUFFER_BIT);
			
			for (auto gameObject : objects)
			{
				glUniformMatrix4fv(glGetUniformLocation(shader, "lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(shadowOrthoProj[i]));

				gameObject->shader = shader;
				gameObject->shaderName = "depthMap";

				if (gameObject->meshRenderer != nullptr)
				{
					gameObject->meshRenderer->SetShader(shader);

				}

				gameObject->Draw();
			}

		}
		
		glCullFace(GL_BACK);

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
		glUniform1f(glGetUniformLocation(shader, "near_plane"), shadowMapCascades[0]);
		glUniform1f(glGetUniformLocation(shader, "far_plane"), shadowMapCascades[3]);


		for (unsigned int i = 0; i < NUM_CASCADES; i++)
		{
			glActiveTexture(GL_TEXTURE4 + i);
			glBindTexture(GL_TEXTURE_2D, shadowTextures[i]);
			glUniform1i(glGetUniformLocation(shader, ("shadowMaps[" + to_string(i) + "]").c_str()), 4 + i);

			glUniformMatrix4fv(glGetUniformLocation(shader, ("lightSpaceMatrix[" + to_string(i) + "]").c_str()), 1, GL_FALSE, glm::value_ptr(shadowOrthoProj[i]));
		}

		glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));

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

		glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(mat4(1.0)));

		DrawQuad();

		/*Draw Shadow Maps*/

		/*Camera * camera = Camera::mainCamera;
		float aspectRatio = camera->GetAspectRatio();

		shader = GameEngine::manager.shaderManager.GetShader("depthDebug");

		glUseProgram(shader);

		textures = shadowBuffer->GetTextures();

		mat4 model = mat4(1.0);
		model = translate(model, vec3(0.6, 0.8, -1));
		model = scale(model, vec3(0.1, 0.1 * aspectRatio, 1));
		glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(shader, "near_plane"), shadowMapCascades[0]);
		glUniform1f(glGetUniformLocation(shader, "far_plane"), shadowMapCascades[1]);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glUniform1i(glGetUniformLocation(shader, "depthMap"), 0);

		DrawQuad();

		model = mat4(1.0);
		model = translate(model, vec3(0.6, 0.2, -1));
		model = scale(model, vec3(0.1, 0.1 *aspectRatio, 1));
		glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(shader, "near_plane"), shadowMapCascades[1]);
		glUniform1f(glGetUniformLocation(shader, "far_plane"), shadowMapCascades[2]);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textures[1]);
		glUniform1i(glGetUniformLocation(shader, "depthMap"), 0);

		DrawQuad();

		model = mat4(1.0);
		model = translate(model, vec3(0.6, -0.8, -1));
		model = scale(model, vec3(0.1, 0.1 *aspectRatio, 1));
		glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(shader, "near_plane"), shadowMapCascades[2]);
		glUniform1f(glGetUniformLocation(shader, "far_plane"), shadowMapCascades[3]);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textures[2]);
		glUniform1i(glGetUniformLocation(shader, "depthMap"), 0);

		DrawQuad();*/

	}
	void DefferredRenderer::TestDepthMap()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); //Write to default

		unsigned int shader = GameEngine::manager.shaderManager.GetShader("depthDebug");

		glUseProgram(shader);

		auto textures = shadowBuffer->GetTextures(); // 0 Texture, 1 Bloom texture
		Camera *c = Camera::mainCamera;

		int texture = 1;
		glUniform1f(glGetUniformLocation(shader, "near_plane"), shadowMapCascades[texture]);
		glUniform1f(glGetUniformLocation(shader, "far_plane"), shadowMapCascades[texture+1]);

		//Set Uniform Location for texture0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textures[texture]);
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

		vec3 camPos = camera->transform->GetPosition();

		//Get the lightspace transform
		const Light * directional = LightManager::Get()->GetLights(DIRECTIONAL_LIGHT)[0];
		vec3 lightDir = -normalize(directional->transform->GetPosition());

		vec3 right = normalize(vec3(1, 0, 0));
		vec3 up = cross(right, normalize(lightDir));
		float aspectRatio = camera->GetAspectRatio();
		float fov = camera->GetFOV();


		float tanFoV = tanf(radians(fov/2.0f));


		mat4 lightView = lookAt(vec3(0), lightDir, up);

		for (unsigned int i = 0; i < NUM_CASCADES; i++)
		{
			float hn = 2 * tanFoV * shadowMapCascades[i];
			float wn = hn * aspectRatio;
			float hf = 2 * tanFoV * shadowMapCascades[i + 1];
			float wf = hf * aspectRatio;
			vec3 front = camera->GetFront();
			vec3 cn = camera->transform->GetPosition() + normalize(camera->GetFront()) * shadowMapCascades[i];
			vec3 cf = camera->transform->GetPosition() + normalize(camera->GetFront()) * shadowMapCascades[i + 1];

			vec4 frustumCorners[NUM_FRUSTRUM_CORNERS] = {
				vec4(cn + up * hn / 2.0f - right * wn / 2.0f, 1.0),
				vec4(cn + up * hn / 2.0f + right * wn / 2.0f, 1.0),
				vec4(cn - up * hn / 2.0f - right * wn / 2.0f, 1.0),
				vec4(cn - up * hn / 2.0f + right * wn / 2.0f, 1.0),

				vec4(cf + up * hf / 2.0f - right * wf / 2.0f, 1.0),
				vec4(cf + up * hf / 2.0f + right * wf / 2.0f, 1.0),
				vec4(cf - up * hf / 2.0f - right * wf / 2.0f, 1.0),
				vec4(cf - up * hf / 2.0f + right * wf / 2.0f, 1.0),
			}; 

			vec4 frustumCornersL[NUM_FRUSTRUM_CORNERS];

			float minX = std::numeric_limits<float>::max();
			float maxX = std::numeric_limits<float>::min();
			float minY = std::numeric_limits<float>::max();
			float maxY = std::numeric_limits<float>::min();
			float minZ = std::numeric_limits<float>::max();
			float maxZ = std::numeric_limits<float>::min();

			for (unsigned int j = 0; j < NUM_FRUSTRUM_CORNERS; j++)
			{
				vec4 vW = frustumCorners[j]; // Frustum Corners in World Space
				frustumCornersL[j] = lightView * vW;

				minX = min(minX, frustumCornersL[j].x);
				maxX = max(maxX, frustumCornersL[j].x);

				minY = min(minY, frustumCornersL[j].y);
				maxY = max(maxY, frustumCornersL[j].y);

				minZ = min(minZ, frustumCornersL[j].z);
				maxZ = max(maxZ, frustumCornersL[j].z);
			}

			maxX += 200.0f;
			minY = -500.0f;
			maxY = 500.0f;


			vec3 center = vec3(minX + maxX, minY +maxY, minZ +maxZ) / 2.0f;
			
			vec4 centerW = vec4((cn + cf) / 2.0f, 1.0);//inverse(lightView) * vec4(center, 1.0);

			mat4 lightViewMatrix = lookAt(vec3(centerW), vec3(centerW) + lightDir, up);


			shadowOrthoProj[i] = ortho(minX, maxX, minY, maxY, minZ, maxZ) * lightViewMatrix;
			//shadowOrthoProj[i] = camera->GetProjectionMatrix() * view;
		}
	}
}