/*
	AI Model for loading the model from file and getting mesh data
	Dev: John Honkanen
*/


#pragma once
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include "Shape.h"
#include "MeshData.h"

namespace Engine {
	class AiModel :public Shape
	{
	public:
		AiModel();
		AiModel(std::string path);
		~AiModel();
		void Init();
		//Sets the filepath to thee model
		void SetModelPath(const std::string& p) { path = p; };
	private:
		//Calls the Assimp loadmodel
		void LoadModel(const std::string& pFile);
		//Extract the mesh data from ai mesh
		MeshData LoadData(aiMesh *mesh);
		Material LoadMaterial(const aiScene *scene, int index);
		std::string getTexturePath(aiMaterial *material, aiTextureType type);

		std::string directory;
		std::string path;
	};
}
