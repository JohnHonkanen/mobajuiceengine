#pragma once
#include "../Behaviour.h"
#include "../Render/ShaderManager.h"
#include <SDL.h>								// Base SDL is needed for SDL attributes and methods
#include <SDL_ttf.h>							// Needs the extension to use the True type fonts

namespace Engine {

	class Text2D : public Behaviour
	{
	private:
		unsigned int textVAO, textVBO, textTexture;
		void SetupVAO();
		void SetupTexture();
		string stringText;
		SDL_Color stringColour;
		TTF_Font *textFont;
		ShaderManager *shaderManager;
	public:
		static unsigned int mainVAO;
		Text2D(string stringText, SDL_Color stringColour, TTF_Font *textFont);
		void Start();
		void Draw();
		void Update();
		static Text2D* Create(GameObject* gameObject, ShaderManager* shaderManager, string stringText, SDL_Color stringColour, TTF_Font *textFont);
	};
}
