#include "components/Terrain.h"
#include "../_Libs/simplex/SimplexNoise.h"
#include "core/GameEngine.h"
#include "components/Camera.h"
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <GL\glew.h>
namespace Engine {
	Terrain::Terrain()
	{
	}
	Terrain::~Terrain()
	{
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(4, vbo);
	}
	Terrain * Terrain::Create(GameObject * obj, float gridSize, unsigned xLength, unsigned zLength, string shader)
	{
		return Create(obj, gridSize, xLength, zLength, 0.0003f, 30.0f, shader);
	}
	Terrain * Terrain::Create(GameObject * obj, float gridSize, unsigned xLength, unsigned zLength, float freq, float weight, string shader)
	{
		Terrain *t = new Terrain();
		t->gridSize = gridSize;
		t->xLength = xLength;
		t->zLength = zLength;
		t->freq = freq;
		t->weight = weight;
		t->shader = shader;

		obj->AddComponent(t);

		return t;

	}
	void Terrain::OnLoad()
	{
		if (seed == -1)
			seed = rand() % 999999;

		PreGenerateHeightMap();
		BuildVertices();
		GenerateIndices();
		GenerateNormals();

		GenerateVAO();
	}
	void Terrain::Draw()
	{
		GLuint program = GameEngine::manager.shaderManager.GetShader(shader);

		glUseProgram(program);

		glm::mat4 projection(1.0);
		projection = Camera::mainCamera->GetProjectionMatrix();
		Camera::mainCamera->CalculateViewMatrix();
		glm::mat4 view = Camera::mainCamera->GetViewMatrix();

		mat4 model(1.0);
		vec3 offset = vec3((xLength * gridSize) / 2, 0, (zLength * gridSize) / 2);
		model = translate(model, -offset);

		glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, glm::value_ptr(view));

		glActiveTexture(GL_TEXTURE0);
		TextureManager *tm = &GameEngine::manager.textureManager;
		glBindTexture(GL_TEXTURE_2D, tm->getTexture(material.diffuseMap));
		glUniform1i(glGetUniformLocation(program, "texture0"), 0);


		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLE_STRIP, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

	}
	void Terrain::GenerateVAO()
	{
		glGenVertexArrays(1, &vao);
		glGenBuffers(4, vbo);

		glBindVertexArray(vao);

		//Position Data
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, verts.size() *  3 * sizeof(float), &verts[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0); //Layout Location 0, position
		glEnableVertexAttribArray(0);

		//UV Data
		glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
		glBufferData(GL_ARRAY_BUFFER, uv.size() * 2 * sizeof(float), &uv[0], GL_STATIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0); //Layout Location 1, UV
		glEnableVertexAttribArray(1);

		//Normals
		glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
		glBufferData(GL_ARRAY_BUFFER, normals.size() * 3 * sizeof(float), &normals[0], GL_STATIC_DRAW);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0); //Layout Location 1, UV
		glEnableVertexAttribArray(2);


	}
	void Terrain::PreGenerateHeightMap()
	{
		heightmap.resize(zLength);

		for (int i = 0; i < zLength; i++) {
			heightmap[i].resize(xLength);
		}
	}
	void Terrain::BuildVertices()
	{
		verts.resize( zLength * xLength);
		uv.resize(verts.size());

		float texU = 1.0f, texV = 1.0f;
		
		int vertex = 0;
		for (int z = 0; z < zLength; z++) {
			for (int x = 0; x < xLength; x++) {

				float scaleU = z / float(zLength - 1) *gridSize;
				float scaleV = x / float(xLength - 1) *gridSize;

				float height;
				//Single Pass heightmap
				height = SimplexNoise::noise((x * seed)  * freq * gridSize, (z * seed) * freq * gridSize) * weight;

				heightmap[z][x] = height;
				verts[vertex] = vec3(x *gridSize, height, z * gridSize);
				uv[vertex] = vec2(texU * scaleU, texV * scaleV);

				vertex++;
			}
		}
	}
	void Terrain::GenerateNormals()
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
				p3 = vec3(xLength * gridSize, 0, zLength * gridSize);
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
	void Terrain::GenerateIndices()
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
				indices[offset++] = ((z+1) * zLength) + x;
			}

			if (z < zLength - 2) {
				//Degenerate End
				indices[offset++] = ((z+1) * zLength) + (xLength -1);
			}
		}
	}
}

