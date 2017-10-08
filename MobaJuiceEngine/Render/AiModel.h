/*
	AI Model for loading the model from file and getting mesh data
	Dev: John Honkanen
*/


#pragma once
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

class AiModel
{
public:
	AiModel();
	~AiModel();

private:
	aiMesh *LoadModel(const std::string& pFile);
	std::string directory;
	const aiScene *scene;
	aiMesh *mesh;
};