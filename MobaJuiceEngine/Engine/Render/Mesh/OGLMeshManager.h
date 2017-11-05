#pragma once
#include "Mesh.h"
#include "MeshData.h"
#include "../../Dictionary.h"
#include "Shape.h"
#include "../ShaderManager.h"
#include "../Texture/TextureManager.h"
#include <memory>
#include <GL\glew.h>
#include <map>

namespace Engine {

	#define STORED_VERTEX       0
	#define STORED_COLOR        1
	#define STORED_UV           2
	#define STORED_NORMAL		3
	#define STORED_INDEX		4
	#define STORED_TANGENT		5
	#define STORED_BITANGENT	6

	typedef std::unique_ptr<Mesh> MeshUniqPtr;
	class OGLMeshManager {
	public:
		OGLMeshManager() {};
		~OGLMeshManager();
		/*
			Get the Mesh with this path. If not already loaded load it.
			@param path	Path to the mesh/ ID.
			@return	The mesh requested,

		*/
		Mesh* GetMesh(std::string path);

		/*
			Sets the shader program to be used by all the meshes by default.
			@param	string name of the shader program in the shader manager
			@param shaderManager	shaderManger that holds the list of shaders
		*/
		void SetShaderProgram(string program, ShaderManager *shaderManager);
		/*
			
		*/
		void SetTextureManager(TextureManager *textureManger);
		ShaderManager *getShaderManager();
	private:	
		void CreateMesh(std::string path);
		void CreateMesh(std::string path, Shape *shape);
		GLuint GenerateVAO(MeshData data);

		std::map<std::string, MeshUniqPtr> meshDictionary;
		std::map<GLuint, GLuint*> VAOMap;
		std::string shaderProgram;
		ShaderManager *shaderManager;
		TextureManager *textureManager;
	};
}