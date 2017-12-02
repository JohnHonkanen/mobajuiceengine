#pragma once
#include <GL\glew.h>
namespace Engine {
	struct Texture
	{
	public:
		enum TYPE {
			DIFFUSE = 0,
			SPECULAR = 1,
			EMISSION = 2,
			BACKGROUND_TEXTURE = 3,
			R_TEXTURE = 4,
			G_TEXTURE = 5,
			B_TEXTURE = 6,
			BLEND_MAP = 7,
			NORMAL_MAP = 8, // Bump Map
			NO_TEXTURE_TYPE = -1
		};

		TYPE type;
		GLuint id;
	};
}