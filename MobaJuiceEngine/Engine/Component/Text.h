//#pragma once
//#include <glm\glm.hpp>							// glm is needed for translations, rotations etc
//#include <glm\ext.hpp>
//#include <glm\gtc\matrix_transform.hpp>
//#include <glm\gtc\type_ptr.hpp>
//
//#include <GL\glew.h>							// glew is needed for primative data types
//#include <string>								// string for conversions in the draw methods
//#include <stack>								// Needs to use a stack
//#include <SDL.h>								// Base SDL is needed for SDL attributes and methods
//#include <SDL_ttf.h>							// Needs the extension to use the True type fonts
//#include <iostream>								// Used for input and output for text
//#include "../Component.h"
//
//using namespace std;	// Needed for std data types
//using glm::vec3;		// vec3 is called here as we use vec3s in calculations
//
//namespace Engine
//{
//	class Text : public Component
//	{
//	private:
//		TTF_Font* textFont; // sets up a pointer to the textFont
//		SDL_Color textColour = { 255,255,255 }; // default text colour is white
//		GLuint label[10]; // HUD labels
//		GLuint meshIndexCount;
//		GLuint meshObject;
//		// GLuints defined for meshObjects
//		static const GLuint textStringLengthSet = 51;
//		// const cannot be changed after initialisation but initialisation processes might sneak in and 
//		// change it at some point during init, for this reason it has been made static so it will never be changed.
//	public:
//		Text();
//		void Load(); // method for loading the HUD
//		void Draw(stack<glm::mat4> mvStack, GLuint shaderProgram); // draw method that takes the stack, and a shader.
//		void Draw(stack<glm::mat4> mvStack, int specularV, GLuint shaderProgram); // draw method that takes the stack, the specular value of the light and a shader.
//		void Draw(stack<glm::mat4> mvStack, GLuint shaderProgram, GLuint labelNumber, vec3 position, vec3 scale, SDL_Color color); // draw method that takes the stack, a shader and the number of the label to be drawn along with a position, scale and colour.
//		GLuint TextToTexture(const char * str, GLuint textID, SDL_Color col); // method for converting the text to a texture on a mesh
//		void ClearTextTexture(GLuint textID); // clears texture updates to avoid memeory leak
//
//	};
//}
//
