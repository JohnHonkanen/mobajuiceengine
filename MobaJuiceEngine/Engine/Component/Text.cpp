//#include "Text.h"
//#include <vector>
//
//
//namespace Engine {
//	Text::Text()
//	{
//		unsigned int textVAO;
//		unsigned int textVBO;
//		if (textVAO == 0)
//		{
//			float textVertices[] = {
//				// positions        // texture Coords
//				-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
//				-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
//				1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
//				1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
//			};
//			// setup plane VAO
//			glGenVertexArrays(1, &textVAO);
//			glGenBuffers(1, &textVBO);
//			glBindVertexArray(textVAO);
//			glBindBuffer(GL_ARRAY_BUFFER, textVBO);
//			glBufferData(GL_ARRAY_BUFFER, sizeof(textVertices), &textVertices, GL_STATIC_DRAW);
//			glEnableVertexAttribArray(0);
//			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//			glEnableVertexAttribArray(1);
//			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//		}
//		glBindVertexArray(textVAO);
//		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
//		glBindVertexArray(0);
//		
//		//rt3d::loadObj("cube.obj", verts, norms, tex_coords, indices);
//		// loads a cube from an external file and applies the norms and vertices along with texture coordinates
//		GLuint size = indices.size();
//		meshIndexCount = size;
//		meshObject = rt3d::createMesh(textVertices.size() / 3, textVertices.data(), nullptr, norms.data(), tex_coords.data(), size, indices.data());
//		//creates the mesh for the texture to be applied to with the above variables
//	}
//
//	void Text::Load()
//	{
//		// set up TrueType / SDL_ttf
//		if (TTF_Init() == -1)
//		{
//			cout << "TTF failed to initialise." << endl;
//		}
//		// a catch for failure of initialisation of the Font
//		textFont = TTF_OpenFont("MavenPro-Regular.ttf", 36); // sets the font to the desired type and font size if the font file has the option
//		if (textFont == NULL)
//		{
//			cout << "Failed to open font." << endl;
//		}
//		// if the font is null a debug text will be output
//			label[0] = 0;
//			label[1] = 0;
//			label[2] = 0;
//			label[3] = 0;
//			label[4] = 0;
//			label[5] = 0;
//			label[6] = 0;
//			label[7] = 0;
//			label[8] = 0;
//			label[9] = 0;
//		// clears the labels to prevent memory leakage
//	}
//
//	// Takes a character array for the output text, the text ID number and a colour
//	GLuint Text::TextToTexture(const char * str, GLuint textID, SDL_Color col)
//
//	{
//		GLuint texture = textID;
//		TTF_Font * font = textFont;
//		//SDL_Color textColour = col;
//		int w = 10, h = 10;
//		//TTF_SizeText(font, str, &w, &h);
//
//		SDL_Surface * stringImage = TTF_RenderText_Blended(font, str, col);
//		// uses a stringImage to render the text with appropriate font, output and colour
//
//		if (stringImage == NULL)
//		{
//			std::cout << "String surface not created." << std::endl;
//		}// if there is a null value in stringImage a debug string is output
//
//		if (texture == 0)
//		{
//			glGenTextures(1, &texture);
//		}// To avoid memory leaks the texutre is only initliased once
//
//		glBindTexture(GL_TEXTURE_2D, texture);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, stringImage->w, stringImage->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, stringImage->pixels);
//		glBindTexture(GL_TEXTURE_2D, NULL);
//		// This creates a texture from the string using stingImage width and height along with the BindTexture and TextParemeteri and TextImage2D methods
//
//		SDL_FreeSurface(stringImage); // This frees the RGB surface of the texture
//		return texture;
//	}
//
//	// Clears the texture if the textID is empty
//	void Text::ClearTextTexture(GLuint textID)
//	{
//		if (textID != NULL) {
//			glDeleteTextures(1, &textID); // if the textID is empty the texture is cleared
//		}
//	}
//
//	// Draws a GUI item that displays the keymaps for debugging
//	void Text::Draw(stack<glm::mat4> mvStack, GLuint shaderProgram)
//	{
//		string key[9];
//		key[0] = ""; // Blank to account for the start of the array.
//
//		key[1] = "Left Shift & Num Pad - Decrease Specular Shininess";
//		key[2] = "Left Shift & Num Pad + Increase Specular Shininess";
//		key[3] = "Num Key 8 - Loads Lightmap Texture only";
//		key[4] = "Num Key 7 - Loads Compounds Texture";
//		key[5] = "Num Key 6 - Loads MetalBox2 Texture Pair";
//		key[6] = "Num Key 5 - Loads MetalBox Texture Pair";
//		key[7] = "Num Key 4 - Inverse Rotate Cubes";
//		key[8] = "Num Key 3 - Rotate Cubes";
//		// Strings for keys loaded.
//
//		// i is defined by which entries in the string array are being used, in this case 1 - 8
//		for (int i = 1; i < 9; i++)
//		{
//			// The strings are all made the same length so that they scale properly when drawn
//			while (key[i].length() < textStringLengthSet)// This makes all the keys the same length
//			{
//				key[i] += " ";
//			}
//
//			glUseProgram(shaderProgram); //Use texture-only shader for text rendering
//			glDisable(GL_DEPTH_TEST); //Disable depth test for HUD label
//			glBindTexture(GL_TEXTURE_2D, label[i]); // applies the texture
//			mvStack.push(glm::mat4(1.0));
//			mvStack.top() = glm::translate(mvStack.top(), glm::vec3(-0.575f, (-1.1f + (0.2*i)), 0.0f));
//			mvStack.top() = glm::scale(mvStack.top(), glm::vec3(0.4, 0.1f, 0.0f));
//			// moves and scales the texture.
//			glUniformMatrix4fv(shaderProgram, "projection", glm::value_ptr(glm::mat4(1.0)));
//			// resets the projection matrix so that the label will become 2D
//			rt3d::setUniformMatrix4fv(shaderProgram, "modelview", glm::value_ptr(mvStack.top()));
//			// gets the shader program for drawing so that the label will always be seen
//
//			rt3d::drawIndexedMesh(meshObject, meshIndexCount, GL_TRIANGLES);
//			mvStack.pop();
//			glEnable(GL_DEPTH_TEST);//Re-enable depth test after HUD label
//
//			label[i] = textToTexture(key[i].c_str(), label[i], { 255,0,255 });
//		}
//
//	}
//
//	// Draws a HUD that displays the Specular Shininess value of the scene object.
//	// Takes the specular value of the object and the shader program along with the modelView stack as parameters.
//	void Text::Draw(stack<glm::mat4> mvStack, int specularV, GLuint shaderProgram)
//	{
//		glUseProgram(shaderProgram); //Use texture-only shader for text rendering
//		glDisable(GL_DEPTH_TEST); //Disable depth test for HUD label
//		glBindTexture(GL_TEXTURE_2D, label[0]); // applies the texture
//		mvStack.push(glm::mat4(1.0));
//		mvStack.top() = glm::translate(mvStack.top(), glm::vec3(-0.5f, 0.8f, 0.0f));
//		mvStack.top() = glm::scale(mvStack.top(), (glm::vec3(0.6, 0.3, 0.0f)));
//		// moves and scales the texture.
//		rt3d::setUniformMatrix4fv(shaderProgram, "projection", glm::value_ptr(glm::mat4(1.0)));
//		// resets the projection matrix so that the label will become 2D
//		rt3d::setUniformMatrix4fv(shaderProgram, "modelview", glm::value_ptr(mvStack.top()));
//		// gets the shader program for drawing so that the label will always be seen
//
//		rt3d::drawIndexedMesh(meshObject, meshIndexCount, GL_TRIANGLES);
//		mvStack.pop();
//		glEnable(GL_DEPTH_TEST);//Re-enable depth test after HUD label
//
//								//string hudOutput = (" Specular Shininess: " + to_string(specularV));
//		vec3 value = vec3(1, 2, 3);
//		value += 1;
//		float valueX = value.x
//			, valueY = value.y
//			, valueZ = value.z;
//		string fullValue, hud1, hud2, hud3;
//		hud1 = to_string(valueX);
//		hud2 = to_string(valueY);
//		hud3 = to_string(valueZ);
//		string fullHudOutput = (" Specular Shininess: " + hud1 + "," + hud2 + "," + hud3);
//
//		label[0] = textToTexture(fullHudOutput.c_str(), label[0], { 255,0,255 });// calls textToTexture giving the string, the label it is to be placed on and the colour
//	}
//
//	// Draws a HUD that displays a specifically defined label on the screen.
//	// Allows the definition of position, scale and colour from instantiation of the label.
//	void Text::Draw(stack<glm::mat4> mvStack, GLuint shaderProgram, GLuint labelNumber, vec3 position, vec3 scale, SDL_Color color)
//	{
//		glUseProgram(shaderProgram); //Use texture-only shader for text rendering
//		glDisable(GL_DEPTH_TEST); //Disable depth test for HUD label
//		glBindTexture(GL_TEXTURE_2D, label[labelNumber]); // applies the texture
//		mvStack.push(glm::mat4(1.0));
//		mvStack.top() = glm::translate(mvStack.top(), position);
//		mvStack.top() = glm::scale(mvStack.top(), scale);
//		// moves and scales the texture.
//		rt3d::setUniformMatrix4fv(shaderProgram, "projection", glm::value_ptr(glm::mat4(1.0)));
//		// resets the projection matrix so that the label will become 2D
//		rt3d::setUniformMatrix4fv(shaderProgram, "modelview", glm::value_ptr(mvStack.top()));
//		// gets the shader program for drawing so that the label will always be seen
//
//		rt3d::drawIndexedMesh(meshObject, meshIndexCount, GL_TRIANGLES);
//		mvStack.pop();
//		glEnable(GL_DEPTH_TEST);//Re-enable depth test after HUD label
//
//		string hudOutput = (" Jack D Smith ");
//
//		/*while (hudOutput.length() < textStringLengthSet) // This will normlaize the length of the string to a uniform size. No need for constant scaling.
//		{
//		hudOutput += " ";
//		}*/
//
//		label[labelNumber] = TextToTexture(hudOutput.c_str(), label[labelNumber], color);// calls textToTexture giving the string, the label it is to be placed on and the colour
//	}
//
//
//}