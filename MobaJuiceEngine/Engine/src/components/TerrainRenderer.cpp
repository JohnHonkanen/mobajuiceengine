#include "components\TerrainRenderer.h"
#include "core\GameEngine.h"
#include "components\Camera.h"
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "GL\glew.h"
namespace Engine {
	namespace Terrain{
		TerrainRenderer::TerrainRenderer()
		{
		}
		TerrainRenderer::~TerrainRenderer()
		{
		}
		TerrainRenderer * TerrainRenderer::Create(GameObject * gameObject, string diffuse, string shader)
		{
			TerrainGrid *grid = gameObject->GetComponent<TerrainGrid>();

			if (grid == nullptr) {
				assert(0); //Your Grid Was not found. Please add it first
			}

			TerrainRenderer *tr = new TerrainRenderer();
			tr->grid = grid;
			tr->preloaded = true;
			tr->material.diffuseMap = diffuse;
			tr->shader = shader;

			grid->GetData(tr->verts, tr->uv, tr->normals, tr->xLength, tr->zLength);
			tr->GenerateIndices();

			gameObject->AddComponent(tr);
			gameObject->SetRenderMode(DEFERRED);

			return tr;
		}
		void TerrainRenderer::Copy(GameObject * copyObject)
		{
			TerrainRenderer *tr = new TerrainRenderer();
			tr->material.diffuseMap = material.diffuseMap;
			tr->shader = shader;

			copyObject->AddComponent(tr);
			copyObject->SetRenderMode(DEFERRED);
		}
		void TerrainRenderer::OnLoad()
		{
			if (!preloaded)
			{
				TerrainGrid *grid = gameObject->GetComponent<TerrainGrid>();
				TerrainRenderer::grid = grid;
				grid->GetData(verts, uv, normals, xLength, zLength);
				GenerateIndices();
			}

			GenerateVAO();
		}
		void TerrainRenderer::Draw()
		{
			GLuint program;

			if (gameObject->GetRenderMode() == DEFERRED)
			{
				program = gameObject->shader;

			}
			else {
				program = GameEngine::manager.shaderManager.GetShader(shader);
				glUseProgram(program);
			}


			glm::mat4 projection(1.0);
			projection = Camera::mainCamera->GetProjectionMatrix();
			Camera::mainCamera->CalculateViewMatrix();
			glm::mat4 view = Camera::mainCamera->GetViewMatrix();

			mat4 model(1.0);
			model = transform->GetLocalToWorldMatrix();
			model = translate(model, vec3(10, 0, 50));

			glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
			glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, glm::value_ptr(model));
			glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, glm::value_ptr(view));

			glActiveTexture(GL_TEXTURE0);
			TextureManager *tm = &GameEngine::manager.textureManager;
			glBindTexture(GL_TEXTURE_2D, tm->getTexture(material.diffuseMap));
			glUniform1i(glGetUniformLocation(program, "diffuseMap"), 0);

			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, 0);
			glUniform1i(glGetUniformLocation(program, "specularMap"), 1);

			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, 0);
			glUniform1i(glGetUniformLocation(program, "emissionMap"), 2);

			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, 0);
			glUniform1i(glGetUniformLocation(program, "normalMap"), 3);


			glBindVertexArray(vao);
			glDrawElements(GL_TRIANGLE_STRIP, indices.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
		void TerrainRenderer::GenerateVAO()
		{
			glGenVertexArrays(1, &vao);
			glGenBuffers(4, vbo);

			glBindVertexArray(vao);

			//Position Data
			glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
			glBufferData(GL_ARRAY_BUFFER, verts.size() * 3 * sizeof(float), &verts[0], GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0); //Layout Location 0, position
			glEnableVertexAttribArray(0);

			//UV Data
			glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
			glBufferData(GL_ARRAY_BUFFER, uv.size() * 2 * sizeof(float), &uv[0], GL_STATIC_DRAW);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0); //Layout Location 1, UV
			glEnableVertexAttribArray(2);

			//Normals
			glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
			glBufferData(GL_ARRAY_BUFFER, normals.size() * 3 * sizeof(float), &normals[0], GL_STATIC_DRAW);
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
			glEnableVertexAttribArray(3);
		}

		void TerrainRenderer::GenerateIndices()
		{
			const int numStrips = zLength - 1;
			const int numDegens = 2 * (numStrips - 1);
			const int vps = 2 * xLength; // Vertices per strip

			indices.resize((vps * numStrips) + numDegens);
			int offset = 0;

			for (int z = 0; z < zLength - 1; z++) {
				if (z > 0) {
					//Degenerate begin
					indices[offset++] = z * zLength;
				}

				for (int x = 0; x < xLength; x++) {
					indices[offset++] = (z * zLength) + x;
					indices[offset++] = ((z + 1) * zLength) + x;
				}

				if (z < zLength - 2) {
					//Degenerate End
					indices[offset++] = ((z + 1) * zLength) + (xLength - 1);
				}
			}
		}
	}
}