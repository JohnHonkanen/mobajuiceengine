#include "hud\utility\Font.h"
#include <GL\glew.h>
#include <iostream>
#include <ft2build.h>
#include FT_FREETYPE_H

namespace Engine
{
	namespace Utility
	{

		Font::Font(std::string name) : name(name) {
		}

		std::map<char, Character> Font::GetCharacters(unsigned int fontsize )
		{
			auto it = characters.find(fontsize);
			if (it == characters.end()) {
				LoadFont(name, fontsize);
			}

			return characters.at(fontsize);
		}

		void Font::LoadFont(std::string name, unsigned int fontsize)
		{
			FT_Library ft;
			// All functions return a value different than 0 whenever an error occurred
			if (FT_Init_FreeType(&ft))
			{
				std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
				return;
			}

			FT_Face face;
			if (FT_New_Face(ft, name.c_str(), 0, &face))
			{
				std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
				return;
			}
				
			// Set size to load glyphs as
			FT_Set_Pixel_Sizes(face, 0, fontsize);

			glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

			std::map<char, Character> characterGlyph;
			// Load first 128 characters of ASCII set
			for (GLubyte c = 0; c < 128; c++)
			{
				// Load character glyph 
				if (FT_Load_Char(face, c, FT_LOAD_RENDER))
				{
					std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
					continue;
				}
				// Generate texture
				GLuint texture;
				glGenTextures(1, &texture);
				glBindTexture(GL_TEXTURE_2D, texture);
				glTexImage2D(
					GL_TEXTURE_2D,
					0,
					GL_RED,
					face->glyph->bitmap.width,
					face->glyph->bitmap.rows,
					0,
					GL_RED,
					GL_UNSIGNED_BYTE,
					face->glyph->bitmap.buffer
				);
				// Set texture options
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				// Now store character for later use
				Character character = {
					texture,
					glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
					glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
					face->glyph->advance.x
				};

				characterGlyph.insert(std::pair<char, Character>(c, character));
			}

			characters.insert(std::pair<unsigned int, std::map<char, Character>>(fontsize, characterGlyph));
			// Destroy FreeType once we're finished
			FT_Done_Face(face);
			FT_Done_FreeType(ft);
		}
	}
}