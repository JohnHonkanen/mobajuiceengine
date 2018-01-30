#pragma once
#include <glm\glm.hpp>
#include <string>
#include <map>

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
			std::map<char, Character> GetCharacters() const;
		private:
			void LoadFont(std::string name);

			//Character map
			std::map<char, Character> characters;
		};
	}
}

