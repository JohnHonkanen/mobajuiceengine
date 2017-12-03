#include "render/texture/TextureManager.h"
#include <IL\il.h>
#include <iostream>
#include <string>
namespace Engine {
	TextureManager::TextureManager()
	{
	}

	TextureManager::~TextureManager()
	{
		for each (auto texture in textures)
		{
			glDeleteTextures(1, &texture.second);
		}
		
	}

	GLuint TextureManager::getTexture(string texture)
	{
		auto it = textures.find(texture);
		if (it != textures.end()) {
			return textures[texture];
		}
		//Create Texture

		saveTexture(texture);

		return textures[texture];
	}
	GLuint TextureManager::getTexture(string texture, bool CubeMap)
	{
		if (!CubeMap)
			return getTexture(texture);

		auto it = textures.find(texture);
		if (it != textures.end()) {
			return textures[texture];
		}

		if (saveTexture(texture, true)) {
			return textures[texture];
		}

		return 0;
		
	}

	bool TextureManager::saveTexture(const string texture, bool CubeMap)
	{
		GLuint cubeMap;
		glGenTextures(1, &cubeMap);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMap);
		string path = texture;
		string type = path.substr(path.find_last_of(".") + 1);

		for (unsigned int i = 0; i < 6; i++) {

			ILuint width;
			ILuint height;

			ILuint tex;

			ilGenImages(1, &tex);
			ilBindImage(tex);

			string image = path.substr(0, path.find_last_of('/')) + "/CubeMap_" + to_string(i+1) + "." + type;

			if (!ilLoadImage(image.c_str())) {
				cout << ilGetError() << endl;
				return false;
			}

			ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);

			width = ilGetInteger(IL_IMAGE_WIDTH);
			height = ilGetInteger(IL_IMAGE_HEIGHT);

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, ilGetData());

			ilDeleteImages(1, &tex);
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		// De-allocate memory
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

		textures[texture] = cubeMap;

		return true;
	}
	bool TextureManager::saveTexture(const string texture)
	{
		//Image Loader Generation

		ILuint width;
		ILuint height;

		ILuint image;

		ilGenImages(1, &image);
		ilBindImage(image);

		if (ilLoadImage((const ILstring) texture.c_str())) {
		
		}
		else {
			cout << ilGetError() << endl;
			cout << "Failed to load image: " << texture.c_str() << endl;
		}

		//Convert image to a usable image type
		ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

		//Get its width and height
		width = ilGetInteger(IL_IMAGE_WIDTH);
		height = ilGetInteger(IL_IMAGE_HEIGHT);

		//OpenGL texure loading

		GLuint textureID;

		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);

		// Set the texture wrapping parameters
		// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// Set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, ilGetData());

		// Generate mipmap here
		glGenerateMipmap(GL_TEXTURE_2D);
		ilDeleteImages(1, &image); // Deletes image
		glBindTexture(GL_TEXTURE_2D, 0); // Unbinds the texture

		textures.insert(pair<string, GLuint>(texture, textureID));
		return true;
	}
}

