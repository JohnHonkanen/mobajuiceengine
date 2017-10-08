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
	void SetModelPath(const std::string& p) { path = p; };	
private:
	aiMesh *LoadModel(const std::string& pFile);
	MeshData LoadData(aiMesh *mesh);

	std::string directory;
	std::string path;
	const aiScene *scene;
	aiMesh *mesh;
	MeshData data;
};