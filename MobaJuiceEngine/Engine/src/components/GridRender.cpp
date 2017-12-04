#include "components/GridRender.h"
#include "..\..\..\GridRender.h"
#include "core\GameObject.h"


namespace Engine {
	GridRender::GridRender()
	{
	}
	GridRender::~GridRender()
	{
	}

	GridRender * GridRender::Create(GameObject * gameObject)
	{
		Tile* tile = gameObject->GetComponent<Tile>();
		if (tile == nullptr) {
			//Brings debugger here when program fails if tile not found, please add a tile
			assert(0);		
			return nullptr;
		}
		GridRender* gr = new GridRender();
		gr->tile = tile;
		gameObject->AddComponent(gr);
		return gr;
	}

	void GridRender::GridSetup()
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*verticies.size(), &verticies[0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
		glEnableVertexAttribArray(0);
	}
	
	void GridRender::Draw()
	{
			//make grid as big as the viewed area
			unsigned int shader = GameEngine::manager.shaderManager.GetShader("tile");
			glUseProgram(shader);
			mat4 projection = Camera::mainCamera->GetProjectionMatrix();
			mat4 view = Camera::mainCamera->GetViewMatrix();
			mat4 model = transform->GetLocalToWorldMatrix();
			glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
			glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));
			glLineWidth(5);
			glBindVertexArray(VAO);
			glDrawArrays(GL_LINES, 0, verticies.size() / 3);
			glBindVertexArray(0);
	}

	void GridRender::Start()
	{
		tile->GetTileData(gridHeight, gridWidth, cellSize, planeHeight, verticies);
		GridSetup();
		vec3 offset = vec3((cellSize * gridWidth) / 2, 0, (cellSize * gridHeight) / 2);
		transform->Translate(offset);
	}

}