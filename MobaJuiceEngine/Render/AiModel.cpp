#include "AiModel.h"
#include <fstream>
AiModel::AiModel()
{
}

AiModel::~AiModel()
{
}
void AiModel::Init()
{
	if (AiModel::path.empty()) {
		printf("Couldn't open model file: %s\n", path.c_str());
		return;
	}
	AiModel::mesh = AiModel::LoadModel(AiModel::path);
	AiModel::data = AiModel::LoadData(AiModel::mesh);
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

MeshData AiModel::LoadData(aiMesh * mesh)
{
	float *vertexArray;
	float *normalArray;
	float *uvArray;

	int numVerts;

	numVerts = mesh->mNumFaces * 3;

	vertexArray = new float[mesh->mNumFaces * 3 * 3];
	normalArray = new float[mesh->mNumFaces * 3 * 3];
	uvArray = new float[mesh->mNumFaces * 3 * 2];

	for (unsigned int i = 0; i<mesh->mNumFaces; i++)
	{
		const aiFace& face = mesh->mFaces[i];

		for (int j = 0; j<3; j++)
		{
			aiVector3D uv = mesh->mTextureCoords[0][face.mIndices[j]];
			memcpy(uvArray, &uv, sizeof(float) * 2);
			uvArray += 2;

			aiVector3D normal = mesh->mNormals[face.mIndices[j]];
			memcpy(normalArray, &normal, sizeof(float) * 3);
			normalArray += 3;

			aiVector3D pos = mesh->mVertices[face.mIndices[j]];
			memcpy(vertexArray, &pos, sizeof(float) * 3);
			vertexArray += 3;
		}
	}

	uvArray -= mesh->mNumFaces * 3 * 2;
	normalArray -= mesh->mNumFaces * 3 * 3;
	vertexArray -= mesh->mNumFaces * 3 * 3;

	return MeshData{ vertexArray, normalArray, uvArray, numVerts };
}

