#include "components\TerrainGrid.h"
#include "core/GameEngine.h"
#include "utility/SimplexNoise.h"
#include "components/Camera.h"
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <GL\glew.h>

namespace Engine {
	namespace Terrain {
		TerrainGrid::TerrainGrid()
		{
		}
		TerrainGrid::~TerrainGrid()
		{
			glDeleteVertexArrays(1, &vao);
			glDeleteBuffers(2, vbo);
		}
		TerrainGrid * TerrainGrid::Create(GameObject * obj, float gridSize, unsigned xLength, unsigned zLength, 
			float freq, float weight, string shader, bool visualizeGrid)
		{
			return Create(obj, gridSize, xLength, zLength, freq, weight, shader, visualizeGrid, vec3(0,1,0));
		}
		TerrainGrid * TerrainGrid::Create(GameObject * obj, float gridSize, unsigned xLength, unsigned zLength, float freq, float weight, string shader, bool visualizeGrid, vec3 offset)
		{
			TerrainGrid *t = new TerrainGrid();
			t->gridSize = gridSize;
			t->xLength = xLength;
			t->zLength = zLength;
			t->freq = freq;
			t->weight = weight;
			t->shader = shader;
			t->visualizeGrid = visualizeGrid;
			t->offset = offset;

			if (t->seed == -1)
				t->seed = rand() % 999999;

			t->PreGenerateHeightMap();
			t->BuildVertices();
			t->GenerateIndices();

			t->preloaded = true;

			obj->AddComponent(t);

			t->transform->Translate(-vec3((xLength * gridSize) / 2, 0, (zLength * gridSize) / 2));

			return t;
		}
		void TerrainGrid::OnLoad()
		{
			if (!preloaded) {
				PreGenerateHeightMap();
				BuildVertices();
				GenerateIndices();
			}

			if (visualizeGrid) {
				GenerateVAO();
			}
		}
		void TerrainGrid::Draw()
		{
			if (!visualizeGrid)
				return;

			GLuint program = GameEngine::manager.shaderManager.GetShader(shader);

			glUseProgram(program);

			glm::mat4 projection(1.0);
			projection = Camera::mainCamera->GetProjectionMatrix();
			Camera::mainCamera->CalculateViewMatrix();
			glm::mat4 view = Camera::mainCamera->GetViewMatrix();

			mat4 model(1.0);
			model = translate(model, offset);
			model *= transform->GetLocalToWorldMatrix();

			glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
			glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, glm::value_ptr(model));
			glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, glm::value_ptr(view));

			glBindVertexArray(vao);
			glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
		void TerrainGrid::GetData(vector<vec3>& verts, vector<vec2>& uv, unsigned int &xLength, unsigned int &zLength)
		{
			verts = TerrainGrid::verts;
			uv = TerrainGrid::uv;
			xLength = TerrainGrid::xLength;
			zLength = TerrainGrid::zLength;
		}

		float TerrainGrid::GetHeight(float x, float z)
		{
			vec3 tp = transform->GetPosition();
			float terrainX = x - tp.x;
			float terrainZ = z - tp.z;

			float xCoord = ((int)terrainX % (int)gridSize) / (float)gridSize;
			float zCoord = ((int)terrainZ % (int)gridSize) / (float)gridSize;

			int gridX = (int)floor(terrainX / gridSize);
			int gridZ = (int)floor(terrainZ / gridSize);
			float height;
			if (xCoord <= (1 - zCoord)) {
				height = barryCentric(vec3(0, heightmap[gridZ][gridX], 0), vec3(1, heightmap[gridZ][gridX + 1], 0), vec3(0, heightmap[gridZ + 1][gridX], 1), vec2(xCoord, zCoord));
			}
			else {
				height = barryCentric(vec3(1, heightmap[gridZ][gridX + 1], 0), vec3(1, heightmap[gridZ + 1][gridX + 1], 1), vec3(0, heightmap[gridZ + 1][gridX], 1), vec2(xCoord, zCoord));
			}

			return height;
		}

		void TerrainGrid::GenerateVAO()
		{
			glGenVertexArrays(1, &vao);
			glGenBuffers(2, vbo);

			glBindVertexArray(vao);

			//Position Data
			glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
			glBufferData(GL_ARRAY_BUFFER, verts.size() * 3 * sizeof(float), &verts[0], GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0); //Layout Location 0, position
			glEnableVertexAttribArray(0);

			glBindVertexArray(0);
		}
		void TerrainGrid::PreGenerateHeightMap()
		{
			heightmap.resize(zLength);

			for (int i = 0; i < zLength; i++) {
				heightmap[i].resize(xLength);
			}
		}
		void TerrainGrid::BuildVertices()
		{
			verts.resize(zLength * xLength);
			uv.resize(verts.size());

			float texU = 1.0f, texV = 1.0f;

			int vertex = 0;
			for (int z = 0; z < zLength; z++) {
				for (int x = 0; x < xLength; x++) {

					float scaleU = z / float(zLength - 1) *gridSize;
					float scaleV = x / float(xLength - 1) *gridSize;

					float height;
					//Single Pass heightmap
					height = SimplexNoise::noise((x + seed)  * freq * gridSize, (z + seed) * freq * gridSize) * weight;

					heightmap[z][x] = height;
					verts[vertex] = vec3(x *gridSize, height, z * gridSize);
					uv[vertex] = vec2(texU * scaleU, texV * scaleV);

					vertex++;
				}
			}
		}
		void TerrainGrid::GenerateIndices()
		{
			const int numStrips = zLength;
			const int vps = 2 * xLength;
			const int ver = numStrips * vps - (2 * xLength - 1);
			const int lastX = (numStrips +1) * 2;
			indices.resize(numStrips * vps + (ver + lastX));
			unsigned int offset = 0;
			for (int z = 0; z < zLength; z++) {
				for (int x = 0; x < xLength-1; x++) {
					indices[offset++] = (z * zLength) + x;
					indices[offset++] = (z * zLength) + (x + 1);
					

					if (z > 0) {
						indices[offset++] = ((z - 1) * zLength) + x;
						indices[offset++] = (z * zLength) + x;

						if (x == xLength - 2) {
							indices[offset++] = ((z - 1) * zLength) + (x + 1);
							indices[offset++] = (z * zLength) + (x + 1);
						}
					}
				}
			}
		}
	}
}