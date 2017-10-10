/*
	AI Model for loading the model from file and getting mesh data
	Dev: John Honkanen
*/


#pragma once
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include "MeshData.h"

class AiModel
{
public:
	AiModel();
	~AiModel();
	void Init();
	//Sets the filepath to thee model
	void SetModelPath(const std::string& p) { path = p; };	
private:
	//Calls the Assimp loadmodel
	aiMesh *LoadModel(const std::string& pFile);
	//Extract the mesh data from ai mesh
	MeshData LoadData(aiMesh *mesh);

	std::string directory;
	std::string path;
	const aiScene *scene;
	aiMesh *mesh;
	MeshData data;
};