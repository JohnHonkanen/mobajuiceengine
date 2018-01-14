/*
	Contains methods to setup and render Text2D objects.
	Dev: Jack Smith - (B00308927)
*/

#include "components/Text2D.h"						// Includes the Text2d header
#include <GL\glew.h>					// Uses glew for 
#include "glm\gtc\type_ptr.hpp"			// Allows the use of glm::value_ptr() to pass uniforms into shaders
#include "glm\gtc\matrix_transform.hpp" // Allows for orthographic projections to be created
#include "core/GameObject.h"				// GameObject is used to apply gameObject methods to the text objects
#include "components/Camera.h"						// Includes Camera to access its methods

using namespace std;

namespace Engine {

	unsigned int Text2D::mainVAO = 0;	// static field is initialised

										/*
										Sets up the VAO (textVAO) for the quad and generates and binds the buffer object textVBO
										*/
	void Text2D::SetupVAO()
	{
		if (mainVAO == 0)
		{
			float textVertices[] = {
				// positions        // texture Coords
				-1.0f,  1.0f, 0.0f, 0.0f, 0.0f,
				-1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
				1.0f,  1.0f, 0.0f, 1.0f, 0.0f,
				1.0f, -1.0f, 0.0f, 1.0f, 1.0f,
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

			// Pass the VAO to the mainVAO
			mainVAO = textVAO;

		}
		else
		{
			// If the VAO has already been created then reuse it
			textVAO = mainVAO;
		}
		// Bind the vertex array
		glBindVertexArray(0);
	}

	/*
	Converts the string into a texture to be placed on the quad
	*/
	void Text2D::SetupTexture()
	{
		stringColour.r = colourData.x;
		stringColour.g = colourData.y;
		stringColour.b = colourData.z;

		/*
		Uses a stringImage to render the text with appropriate font, output and colour
		@param   textFont	  - The font type of the text
		@param   stringText	  - The string of text to be converted
		@param   stringColour - The colour of the text

		@returns SDL_Surface  - The text texture to be drawn
		*/
		SDL_Surface * stringImage = TTF_RenderText_Blended(textFont, stringText.c_str(), stringColour);

		// a catch for failure of initialisation of the Font
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

	Text2D::Text2D()
	{
	}

	/*
	Constructs a Text2D object by calling setup methods - This makes the passed in fields available to these methods
	@param   stringText	  - The string of text to be converted
	@param   stringColour - The colour of the text
	@param   *textFont	  - The font type of the text

	@returns Text2D      - A constructed Text2D object
	*/
	Text2D::Text2D(string stringText, vec3 colourData, string font) :stringText(stringText), colourData(colourData), font(font)
	{

	}

	void Text2D::Start()
	{
	}

	/*
	Renders the text texture to the sceen
	Tells the program which shader to use and sets up the matricies to be passed into a shader
	Draws the quad
	*/
	void Text2D::Draw()
	{
		glUseProgram(shaderProgram);
		glm::mat4 model = transform->GetLocalToWorldMatrix();
		glm::mat4 projection(1.0);
		projection = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, 0.0f, 100.0f); // Projection set to a 2D orthographic view. 
		Camera::mainCamera->CalculateViewMatrix();
		glm::mat4 view(1.0);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textTexture);
		glUniform1i(glGetUniformLocation(shaderProgram, "texture0"), 0);
		glBindVertexArray(textVAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);
	}

	/*
	Updates the text object with two input values
	@param - value  A user defined float
	@param - value2 A user defined float
	*/
	void Text2D::Update(float value, float value2)
	{
		stringText = to_string(value) + to_string(value2);
	}

	/*
	Creates a new GameObject and assigns a shaderManager object
	Gives gameObject ownership of the Text2D object

	@param - *gameObject    - The Text2D GameObject
	@param - *shaderManager - The shader
	@param - stringText     - The text to be displayed
	@param - stringColour   - The colour of the text
	@param - *textFont	    - The font of the text

	@returns Text2D - Text2D object
	*/
	Text2D * Text2D::Create(GameObject * gameObject, std::string shaderPath, string stringText, vec3 colourData, string font)
	{
		/*
		Creates a new Text2D object
		@param - stringText     - The text to be displayed
		@param - stringColour   - The colour of the text
		@param - *textFont	    - The font of the text

		@returns - Text2D - A new Text2D object
		*/
		Text2D *textObject = new Text2D(stringText, colourData, font);
		textObject->shader = shaderPath;
		//Adds ownership
		gameObject->AddComponent(textObject);

		return textObject;
	}

	void Text2D::Copy(GameObject * copyObject)
	{
		Create(copyObject, shader, stringText, colourData, font);
	}

	void Text2D::OnLoad()
	{
		shaderManager = &GameEngine::manager.shaderManager;
		shaderProgram = shaderManager->GetShader(shader);

		textFont = GameEngine::manager.fontManager.GetFont(font);

		SetupVAO();
		SetupTexture();
	}
}