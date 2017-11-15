#include "Text2D.h"
#include <GL\glew.h>
#include <iostream>		
#include "glm\gtc\type_ptr.hpp"
#include "../GameObject.h"
#include "Camera.h"

using namespace std;

namespace Engine {

	unsigned int Text2D::mainVAO = 0;

	void Text2D::SetupVAO()
	{

		if (mainVAO == 0)
		{
			float textVertices[] = {
				// positions        // texture Coords
				-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
				-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
				1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
				1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
			};
			// setup plane VAO
			glGenVertexArrays(1, &textVAO);
			glGenBuffers(1, &textVBO);
			glBindVertexArray(textVAO);
			glBindBuffer(GL_ARRAY_BUFFER, textVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(textVertices), &textVertices, GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

			mainVAO = textVAO;

		}
		else
		{
			textVAO = mainVAO;
		}
		glBindVertexArray(0);
	}
	void Text2D::SetupTexture()
	{
		SDL_Surface * stringImage = TTF_RenderText_Blended(textFont, stringText.c_str(), stringColour);
		// uses a stringImage to render the text with appropriate font, output and colour

		if (stringImage == NULL)
		{
			std::cout << "String surface not created." << std::endl;
		}// if there is a null value in stringImage a debug string is output

		if (textTexture == 0)
		{
			glGenTextures(1, &textTexture);
		}// To avoid memory leaks the texutre is only initliased once

		glBindTexture(GL_TEXTURE_2D, textTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, stringImage->w, stringImage->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, stringImage->pixels);
		glBindTexture(GL_TEXTURE_2D, NULL);
		// This creates a texture from the string using stingImage width and height along with the BindTexture and TextParemeteri and TextImage2D methods

		SDL_FreeSurface(stringImage); // This frees the RGB surface of the texture
	}
	Text2D::Text2D(string stringText, SDL_Color stringColour, TTF_Font *textFont) :stringText(stringText), stringColour(stringColour), textFont(textFont) 
	{
		SetupVAO();
		SetupTexture();
	}
	void Text2D::Start()
	{
	}
	void Text2D::Render()
	{
		unsigned int shader = shaderManager->GetShader("text2D");
		glUseProgram(shader);
		glm::mat4 model = transform->GetLocalToWorldMatrix();
		glm::mat4 projection(1.0);
		projection = Camera::mainCamera->GetProjectionMatrix();

		Camera::mainCamera->CalculateViewMatrix();
		glm::mat4 view = Camera::mainCamera->GetViewMatrix();

		glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textTexture);
		glUniform1i(glGetUniformLocation(shader, "texture0"), 0);
		glBindVertexArray(textVAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);

			}
	void Text2D::Update()
	{
	}

	Text2D * Text2D::Create(GameObject * gameObject, ShaderManager * shaderManager, string stringText, SDL_Color stringColour, TTF_Font * textFont)
	{
		Text2D* text = new Text2D(stringText, stringColour, textFont);

		text->shaderManager = shaderManager;
		gameObject->AddComponent(text);

		return text;
	}
}