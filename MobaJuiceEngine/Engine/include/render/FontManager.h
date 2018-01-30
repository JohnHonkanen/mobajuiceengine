/*
The FontManager class used to control and manage fonts
Dev: Jack Smith (B000308927), edited by John Honkanen(B00291253)
*/
#pragma once
#include <map>
#include <memory>
#include <SDL.h>								// Base SDL is needed for SDL attributes and methods
#include <SDL_ttf.h>							// Needs the extension to use the True type fonts
#include "hud\utility\Font.h"

using namespace std;
using namespace Engine::Utility;
namespace Engine {

	class FontManager {
	public:
		FontManager();							// Default constructor
		~FontManager();							// Default destructor
		Font * GetFont(std::string name);		// Font accessor


	private:
		void CreateFont(std::string name);		// Creates a new font using a file name
		map<string, unique_ptr<Font>> font;			// map struct used to store a font related to a specific font name from a file
	};
}
