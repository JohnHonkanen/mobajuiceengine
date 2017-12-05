/*
The FontManager class used to control and manage fonts
Dev: Jack Smith (B000308927)
*/
#pragma once
#include <map>
#include <memory>
#include <SDL.h>								// Base SDL is needed for SDL attributes and methods
#include <SDL_ttf.h>							// Needs the extension to use the True type fonts

using namespace std;
namespace Engine {

	class FontManager {
	public:
		FontManager();
		~FontManager();
		TTF_Font * GetFont(std::string name);

	private:
		void CreateFont(std::string name);
		map<string, TTF_Font*> font;
	};
}
