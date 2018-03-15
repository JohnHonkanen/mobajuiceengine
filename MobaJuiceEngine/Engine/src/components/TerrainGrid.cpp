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

		TerrainGrid * TerrainGrid::Create(GameObject * obj, float cellSize, unsigned xLength, unsigned zLength, 
			float freq, float weight, string shader, bool visualizeGrid)
		{
			return Create(obj, cellSize, xLength, zLength, freq, weight, shader, visualizeGrid, vec3(0,1,0));
		}
		TerrainGrid * TerrainGrid::Create(GameObject * obj, float cellSize, unsigned xLength, unsigned zLength, float freq, float weight, string shader, bool visualizeGrid, vec3 offset)
		{
			TerrainGrid *t = new TerrainGrid();
			t->cellSize = cellSize;
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
			t->GenerateNormals();

			t->preloaded = true;

			obj->AddComponent(t);

			t->transform->Translate(-vec3((xLength * cellSize) / 2, 0, (zLength * cellSize) / 2));

			return t;
		}

		void TerrainGrid::Copy(GameObject * copyObject)
		{
			TerrainGrid * copy = Create(copyObject, TerrainGrid::cellSize, TerrainGrid::xLength, TerrainGrid::zLength, TerrainGrid::freq, 
				TerrainGrid::weight, TerrainGrid::shader, TerrainGrid::visualizeGrid, TerrainGrid::offset);
			copy->seed = TerrainGrid::seed;
		}

		void TerrainGrid::OnLoad()
		{
			if (!preloaded) {
				PreGenerateHeightMap();
				BuildVertices();
				GenerateIndices();
				GenerateNormals();
			}

			if (visualizeGrid) {
				GenerateVAO();
			}
		}
		void TerrainGrid::Draw()
		{
			if (!visualizeGrid)
				return;

			GLuint program;

			if (gameObject->GetRenderMode() == DEFERRED)
			{
				program = gameObject->shader;
				if (gameObject->shaderName == "depthMap")
					return;
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
			model = translate(model, offset);
			model *= transform->GetLocalToWorldMatrix();

			glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
			glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, glm::value_ptr(model));
			glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, glm::value_ptr(view));

			glBindVertexArray(vao);
			glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
		void TerrainGrid::GetData(vector<vec3>& verts, vector<vec2>& uv, vector<vec3> &normals, unsigned int &xLength, unsigned int &zLength)
		{
			verts = TerrainGrid::verts;
			uv = TerrainGrid::uv;
			normals = TerrainGrid::normals;
			xLength = TerrainGrid::xLength;
			zLength = TerrainGrid::zLength;
		}

		float TerrainGrid::GetHeight(float x, float z)
		{
			vec3 tp = transform->GetPosition();
			float terrainX = x - tp.x;
			float terrainZ = z - tp.z;

			float xCoord = ((int)terrainX % (int)cellSize) / (float)cellSize;
			float zCoord = ((int)terrainZ % (int)cellSize) / (float)cellSize;

			int gridX = (int)floor(terrainX / cellSize);
			int gridZ = (int)floor(terrainZ / cellSize);
			float height;

			if (gridX > xLength || gridZ > zLength)
				return 0;

			float v1, v2, v3;
			if (xCoord <= (1 - zCoord)) {
				height = barryCentric(vec3(0, heightmap[gridZ][gridX], 0), vec3(1, heightmap[gridZ][gridX + 1], 0), vec3(0, heightmap[gridZ + 1][gridX], 1), vec2(xCoord, zCoord));
			}
			else {
				height = barryCentric(vec3(1, heightmap[gridZ][gridX + 1], 0), vec3(1, heightmap[gridZ + 1][gridX + 1], 1), vec3(0, heightmap[gridZ + 1][gridX], 1), vec2(xCoord, zCoord));
			}

			return height;
		}

		vec3 TerrainGrid::GetSnapPoint(vec3 position)
		{
			vec3 tp = transform->GetPosition();
			float terrainX = position.x - tp.x;
			float terrainZ = position.z - tp.z;

			int gridX = (int)floor(terrainX / cellSize);
			int gridZ = (int)floor(terrainZ / cellSize);


			return vec3(gridX * cellSize, heightmap[gridZ][gridX], gridZ * cellSize) + tp;
		}

		vec2 TerrainGrid::GetCoordinates(vec3 position)
		{
			vec3 tp = transform->GetPosition();
			float terrainX = position.x - tp.x;
			float terrainZ = position.z - tp.z;

			int gridX = (int)floor(terrainX / cellSize);
			int gridZ = (int)floor(terrainZ / cellSize);

			return vec2(gridX, gridZ);
		}

		vec3 TerrainGrid::GetNormal(vec3 position)
		{
			vec3 tp = transform->GetPosition();
			float terrainX = position.x - tp.x;
			float terrainZ = position.z - tp.z;

			int gridX = (int)floor(terrainX / cellSize);
			int gridZ = (int)floor(terrainZ / cellSize);

			return normals[gridZ * zLength + gridX];
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

					float scaleU = z / float(zLength - 1) *cellSize;
					float scaleV = x / float(xLength - 1) *cellSize;

					float height;
					//Single Pass heightmap
					height = SimplexNoise::noise((x + seed)  * freq * cellSize, (z + seed) * freq * cellSize) * weight;

					heightmap[z][x] = height;
					verts[vertex] = vec3(x *cellSize, height, z * cellSize);
					uv[vertex] = vec2(texU * scaleU, texV * scaleV);

					vertex++;
				}
			}
		}
		void TerrainGrid::GenerateNormals()
		{
			vector<vector<vec3>> vectorMap;
			vectorMap.resize(verts.size());

			normals.resize(verts.size());

			unsigned int indexCount = indices.size();
			//Triangle Normal Calculation
			for (int i = 1; i < indexCount;) {
				int v1, v2, v3; //Vertex indices
				vec3 p1, p2, p3; // Points
				vec3 e1, e2; //Edges
				if (i == indexCount - 1) {
					v1 = indices[i - 1];
					v2 = indices[i++];

					p1 = verts[v1];
					p2 = verts[v2];
					p3 = vec3(xLength * cellSize, 0, zLength * cellSize);
				}
				else {
					v1 = indices[i - 1];
					v2 = indices[i++];
					v3 = indices[i++];

					p1 = verts[v1];
					p2 = verts[v2];
					p3 = verts[v3];
				}

				e1 = p2 - p1;
				e2 = p3 - p1;

				vec3 normal = normalize(cross(e1, e2));

				//Check if there is a value, (nullptr == nullptr) = false;
				if (normal.x == normal.x) {

					vectorMap[v1].push_back(normal);
					vectorMap[v2].push_back(normal);

					if (i == indexCount - 1) {
						vectorMap[v3].push_back(normal);
					}
				}
			}
			//Calculate Vertex Normals
			for (int i = 0; i < verts.size(); i++) {
				vector<vec3> trisN = vectorMap[i];
				vec3 sumN(0.0); //Sum of Normals

				for (int n = 0; n < trisN.size(); n++) {
					sumN += trisN[n];
				}

				normals[i] = normalize(sumN);
			}
		}

		void TerrainGrid::GenerateIndices()
		{
			const int numStrips = zLength;
			const int vps = 2 * xLength;
			const int ver = numStrips * vps - (2 * xLength - 1);
			const int lastX = (numStrips + 1) * 2;
			indices.resize(numStrips * vps + (ver + lastX));
			unsigned int offset = 0;
			for (int z = 0; z < zLength; z++) {
				for (int x = 0; x < xLength - 1; x++) {
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