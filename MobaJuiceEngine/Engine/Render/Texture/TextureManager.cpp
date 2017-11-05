#include "TextureManager.h"
#include <IL\il.h>
#include <iostream>
namespace Engine {
	TextureManager::TextureManager()
	{
	}

	TextureManager::~TextureManager()
	{
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
	void TextureManager::saveTexture(const string texture)
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

	}
}

