#pragma once
#include <map>
#include "Texture.h"
using namespace std;
namespace Engine {
	class TextureManager
	{
	public:
		TextureManager();
		~TextureManager();
		/*
			Gets the texture with the followiing name/path. If it is not already stored, create it.
			@param	texture		path/name of texture
			@return	GLuint id of the texture for use in openGL
		*/
		GLuint getTexture(string texture);
		GLuint getTexture(string texture, bool CubeMap);

		
	private:
		bool saveTexture(const string texture, bool CubeMap);
		bool saveTexture(const string texture);
		map<string, GLuint> textures;
	};
}
