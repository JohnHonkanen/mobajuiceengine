/*
	Header containing the fields and method definitions of the Text2D objects.
	Dev: Jack Smith - (B00308927)
*/

#pragma once
#include "Behaviour.h"						// Needs Behaviour to inherit from it
#include "render/ShaderManager.h"			// Uses the shadermanager for rendering
#include <SDL.h>								// Base SDL is needed for SDL attributes and methods
#include <SDL_ttf.h>							// Needs the extension to use the True type fonts
#include "core\GameEngine.h"

namespace Engine {

	class Text2D : public Behaviour
	{
	private:
		unsigned int textVAO, textVBO, textTexture;		// Used for building the quad for the texture
		void SetupVAO();								// Sets up the VAO and binds the VBO for the quad
		void SetupTexture();							// Translates a string into a texture
		string stringText;								// Holds the text string
		SDL_Color stringColour;							// Holds the colour of the string	
		vec3 colourData;								// Holds the colour data in a vec3 format to make is serializeable
		TTF_Font *textFont;								// Holds the font fot the string
		GLuint shaderProgram;							// shaderprogram for creating a shader
		ShaderManager *shaderManager;					// Shadermanager object for accessing it's methods
		std::string shader;								// string to hold a shader file path
		std::string font;								// string to hold a font path
		
	public:
		static unsigned int mainVAO;					// Holds the VAO
		Text2D();
		Text2D(string stringText, vec3 colourData, string font); // Text2D constructor	
		void Start();
		void Draw();									// Renders the text object
		void Update(float value, float value2);			// Updates the text object
		void OnLoad();
		static Text2D* Create(GameObject* gameObject, string shaderPath, string stringText, vec3 colourData, string font);
		// Static factory method that is called when a new Text2D object is created.

		template<class Archive>
		void serialize(Archive & ar) // Serialzation method to save data related to the 2DText
		{
			ar(CEREAL_NVP(stringText), CEREAL_NVP(colourData.x), CEREAL_NVP(colourData.y), CEREAL_NVP(colourData.z), CEREAL_NVP(font), CEREAL_NVP(shader));
		}
	};
}

using namespace Engine;

#include <cereal/archives/xml.hpp>
//Register camera as a derived class
CEREAL_REGISTER_TYPE(Text2D);

//Bind it to the Behaviour
CEREAL_REGISTER_POLYMORPHIC_RELATION(Behaviour, Text2D);