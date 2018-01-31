#include "hud\utility\Font.h"
#include <GL\glew.h>
#include <iostream>

namespace Engine
{
	namespace Utility
	{

		Font::Font(std::string name) {
			if (TTF_Init() == -1)
			{
				assert(0); //Unable to Load TTF_INIT
			}

			LoadFont(name);
		}

		std::map<char, Character> Font::GetCharacters() const
		{
			return characters;
		}

		void Font::LoadFont(std::string name)
		{
			printf("Loading Font: %s \n", name);
			TTF_Font *f = TTF_OpenFont(name.c_str(), 36);

			//If font is not loaded
			if (!f)
			{
				printf("35: TTF_OpenFont: %s\n", TTF_GetError());
				return;
			}

			glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

			//Loop through all available characters
			for (Uint16 unicode = 20; unicode < 128; ++unicode)
			{
				SetupGlyph(unicode, f);
			}
			TTF_CloseFont(f);
		}
		void Font::SetupGlyph(Uint16 c, TTF_Font * f)
		{
			if (!TTF_GlyphIsProvided(f, c)) {
				printf("45: TTF_OpenFont: Glyph is not provided for %i\n", c);
			}
			else {
				unsigned int texture;
				glGenTextures(1, &texture);
				glBindTexture(GL_TEXTURE_2D, texture);

				//Glyph Metrics
				int minX, maxX, minY, maxY, advance;
				TTF_GlyphMetrics(f, c, &minX, &maxX, &minY, &maxY, &advance);

				SDL_Surface * glyph = TTF_RenderGlyph_Blended(f, c, { 255, 255 , 255 });

				unsigned int colors = glyph->format->BytesPerPixel;
				unsigned int texture_format;
				if (colors == 4) {   // alpha
					if (glyph->format->Rmask == 0x000000ff)
						texture_format = GL_RGBA;
					else
						texture_format = GL_BGRA;
				}
				else {             // no alpha
					if (glyph->format->Rmask == 0x000000ff)
						texture_format = GL_RGB;
					else
						texture_format = GL_BGR;
				}
				glTexImage2D(
					GL_TEXTURE_2D,
					0,
					GL_RGB,
					glyph->w,
					glyph->h,
					0,
					GL_RGB,
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
		}
	}
}