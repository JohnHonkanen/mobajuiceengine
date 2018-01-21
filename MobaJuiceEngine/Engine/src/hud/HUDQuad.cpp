#include "hud\HUDQuad.h"
#include <GL\glew.h>

namespace Engine {
	namespace HUD {
		HUDQuad::HUDQuad()
		{
			SetupQuad();
		}

		HUDQuad::~HUDQuad()
		{
			//Clears memory
			glDeleteBuffers(1, &vbo);
			glDeleteVertexArrays(1, &vao);
		}
		
		//Get the vao used for drawing calls
		unsigned int HUDQuad::Get() const
		{
			return vao;
		}

		void HUDQuad::Draw()
		{
			glBindVertexArray(vao);
			glDrawArrays(GL_TRIANGLES, 0, 4);
			glBindVertexArray(0);
		}

		//Set up our quad for drawing
		void HUDQuad::SetupQuad()
		{
			float textVertices[] = {
				// positions        // texture Coords
				-1.0f,  1.0f, 0.0f, 0.0f, 0.0f,
				-1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
				1.0f,  1.0f, 0.0f, 1.0f, 0.0f,
				1.0f, -1.0f, 0.0f, 1.0f, 1.0f,
			};

			unsigned int VAO, VBO;
			// setup plane VAO
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(textVertices), &textVertices, GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

			vao = VAO;
			vbo = VBO;
		}

	}
}