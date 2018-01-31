#pragma once
#include <glm\glm.hpp>
#include <string>
#include <map>
#include <SDL.h>								// Base SDL is needed for SDL attributes and methods
#include <SDL_ttf.h>							// Needs the extension to use the True type fonts

namespace Engine 
{
	namespace Utility
	{
		struct Character
		{
			unsigned int textureID; //Id handle of the glyph texture
			glm::ivec2 size; //Size of the glyph
			glm::ivec2 bearing; //Offset fromt he baseline to left/top of glyph
			unsigned int advance; //Offset to advance to next glpyh
		};

		class Font {
		public:
			Font(std::string name);
			//Get our character map for this font
			std::map<char, Character> GetCharacters(unsigned int fontsize);
		private:
			std::string name;
			void LoadFont(std::string name, unsigned int fontsize);
			//Character map
			std::map<unsigned int, std::map<char, Character>> characters;
		};
	}
}

