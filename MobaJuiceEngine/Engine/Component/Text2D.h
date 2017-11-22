/*
	Header containing the fields and method definitions of the Text2D objects.
	Dev: Jack Smith - (B00308927)
*/

#pragma once
#include "../Behaviour.h"						// Needs Behaviour to inherit from it
#include "../Render/ShaderManager.h"			// Uses the shadermanager for rendering
#include <SDL.h>								// Base SDL is needed for SDL attributes and methods
#include <SDL_ttf.h>							// Needs the extension to use the True type fonts

namespace Engine {

	class Text2D : public Behaviour
	{
	private:
		unsigned int textVAO, textVBO, textTexture;		// Used for building the quad for the texture
		void SetupVAO();								// Sets up the VAO and binds the VBO for the quad
		void SetupTexture();							// Translates a string into a texture
		string stringText;								// Holds the text string
		SDL_Color stringColour;							// Holds the colour of the string
		TTF_Font *textFont;								// Holds the font fot the string
		ShaderManager *shaderManager;					// Shadermanager object for accessing it's methods
	public:
		static unsigned int mainVAO;					// Holds the VAO
		Text2D(string stringText, SDL_Color stringColour, TTF_Font *textFont); // Text2D constructor	
		void Start();									
		void Draw();									// Renders the text object
		void Update(float value, float value2);			// Updates the text object
		static Text2D* Create(GameObject* gameObject, ShaderManager* shaderManager, string stringText, SDL_Color stringColour, TTF_Font *textFont);
		// Static factory method that is called when a new Text2D object is created.
	};
}
