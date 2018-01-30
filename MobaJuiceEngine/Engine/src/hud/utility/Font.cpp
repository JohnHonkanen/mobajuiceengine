#include "hud\utility\Font.h"
#include <SDL.h>								// Base SDL is needed for SDL attributes and methods
#include <SDL_ttf.h>							// Needs the extension to use the True type fonts
#include <GL\glew.h>

namespace Engine
{
	namespace Utility
	{

		Font::Font(std::string name) {
			if (TTF_Init() == -1)
			{
				assert(0); //Unable to Load TTF_INIT
			}
		}

		std::map<char, Character> Font::GetCharacters() const
		{
			return characters;
		}

		void Font::LoadFont(std::string name)
		{
			TTF_Font *f = TTF_OpenFont(name.c_str(), 36);

			//If font is not loaded
			if (!f)
			{
				printf("TTF_OpenFont: %s\n", TTF_GetError());
				return;
			}

			glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

			//Loop through all available characters
			for (GLubyte c = 0; c < 128; c++)
			{
				if (!TTF_GlyphIsProvided(f, c)) {
					printf("%s\n", TTF_GetError());
					return;
				}
				unsigned int texture;
				glGenTextures(1, &texture);
				glBindTexture(GL_TEXTURE_2D, texture);

				//Glyph Metrics
				int minX, maxX, minY, maxY, advance;
				if (!TTF_GlyphMetrics(f, c, &minX, &maxX, &minY, &maxY, &advance))
				{
					//Loading Fail
					printf("%s\n", TTF_GetError());
					return;
				}

				SDL_Surface * glyph = TTF_RenderGlyph_Blended(f, c, {255, 0 ,0});
				glTexImage2D(
					GL_TEXTURE_2D,
					0,
					GL_RED,
					glyph->w,
					glyph->h,
					0,
					GL_RED,
					GL_UNSIGNED_BYTE,
					glyph->pixels
				);

				// Set texture options
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				Character character = 
				{
					texture,
					glm::ivec2(glyph->w, glyph->h),
					glm::ivec2(minX, maxY),
					advance
				};

				characters.insert(std::pair<char, Character>(c, character));
				SDL_FreeSurface(glyph);
			}
			TTF_CloseFont(f);
		}
	}
}