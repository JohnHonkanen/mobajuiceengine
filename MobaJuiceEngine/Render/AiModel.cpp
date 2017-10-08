#include "AiModel.h"
#include <fstream>
AiModel::AiModel()
{
}

AiModel::~AiModel()
{
}
/*
	Loads our Model to a aiMesh Object
	@param pFile File path to Model File
	@return First Mesh in Scene
*/
aiMesh * AiModel::LoadModel(const std::string & pFile)
{
	Assimp::Importer importer;

	//check if file exists
	std::ifstream fin(pFile.c_str());
	if (!fin.fail()) {
		fin.close();
	}
	else {
		printf("Couldn't open file: %s\n", pFile.c_str());
		printf("%s\n", importer.GetErrorString());
		return NULL;
	}

	AiModel::scene = importer.ReadFile(pFile, aiProcessPreset_TargetRealtime_Fast);
	AiModel::directory = pFile.substr(0, pFile.find_last_of('/'));

	//Note: This only returns the first Mesh. For multiple meshes, will need to fix this in the future
	return AiModel::scene->mMeshes[0];
}

