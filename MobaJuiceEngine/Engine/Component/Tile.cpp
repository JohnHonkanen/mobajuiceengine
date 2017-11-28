#include"Tile.h"
#include "../InputManager.h"
#include "../GameEngine.h"
#include "Camera.h"
#include <glm/gtc/type_ptr.hpp>

namespace Engine {
	Tile::Tile()
	{

	}

	Tile::~Tile()
	{

	}

	Tile::Tile(float gWidth, float gHeight, float cWidth, float cHeight, float pHeight)
	{
		gridWidth = gWidth;
		gridHeight = gHeight;
		cellWidth = cWidth;
		cellHeight = cHeight;
		planeHeight = pHeight;
	}

	Tile * Tile::Create(GameObject * gameObject, float gWidth, float gHeight, float cWidth, float cHeight, float pHeight)
	{
		Tile *t = new Tile(gWidth, gHeight, cWidth, cHeight, pHeight);
		gameObject->AddComponent(t);
		return t;
	}

	void Tile::GridSetup()
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*verticies.size(), &verticies[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
	}

	void Tile::GenerateVertices() {

		for (float x = 0; x <= gridWidth; x++) {
			verticies.push_back(x * cellWidth);
			verticies.push_back(planeHeight);
			verticies.push_back(0);

			verticies.push_back(x * cellWidth);
			verticies.push_back(planeHeight);
			verticies.push_back(gridHeight * cellHeight);
		}
		for (float z = 0; z <= gridHeight; z++) {
			verticies.push_back(0);
			verticies.push_back(planeHeight);
			verticies.push_back(z * cellHeight);

			verticies.push_back(gridWidth * cellWidth);
			verticies.push_back(planeHeight);
			verticies.push_back(z * cellHeight);
		}
	}

	void Tile::OnLoad()
	{
		GenerateVertices();
		GridSetup();
	}

	void Tile::Draw()
	{
		unsigned int shader = GameEngine::manager.shaderManager.GetShader("tile");
		glUseProgram(shader);
		mat4 projection = Camera::mainCamera->GetProjectionMatrix();
		mat4 view = Camera::mainCamera->GetViewMatrix();
		glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glLineWidth(5);
		glBindVertexArray(VAO);
		glDrawArrays(GL_LINES, 0, verticies.size() / 3);
		glBindVertexArray(0);
	}

	/*Will change based on defined buildable area, for now stops player building outside of playzone*/
	bool Tile::Buildable(vec3 cell) {
		if ((cell.x >= 0 && cell.x <= gridWidth) && (cell.z >= 0 && cell.z <= gridHeight)) {
			return  true;
		}
		else {
			return false;
		}
	}

	vec3 Tile::GetCell(vec3 mousePosition)
	{
		cell.x = int(mousePosition.x / cellWidth);		//Stores mouse cell position
		cell.y = planeHeight;
		cell.z = int(mousePosition.z / cellHeight);
		return cell;
	}

	vec3 Tile::GetSnapPos(vec3 cell) {
		vec3 snapPos = vec3(cell.x*cellWidth, cell.y, cell.z*cellHeight);
		return snapPos;
	}

	vec3 Tile::GetMouseSnapPos(vec3 mousePosition) {
		vec3 cell = GetCell(mousePosition);
		return GetSnapPos(cell);
	}
}

//http://www.cplusplus.com/forum/general/18315/