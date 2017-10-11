#include "AiModel.h"
#include <fstream>
#include <iostream>
AiModel::AiModel()
{
}

AiModel::AiModel(std::string name)
{
	path = name;
}

AiModel::~AiModel()
{
}
/*
	Intializes our Model. Load and extracts its mesh data.
*/
void AiModel::Init()
{
	if (AiModel::path.empty()) {
		printf("Couldn't open model file: %s\n", path.c_str());
		return;
	}
	AiModel::LoadModel(AiModel::path);

}
/*
	Loads our Model to a aiMesh Object
	@param pFile File path to Model File
	@return First Mesh in Scene
*/
void AiModel::LoadModel(const std::string & pFile)
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
		return;
	}

	const aiScene *scene = importer.ReadFile(pFile, aiProcess_Triangulate | aiProcess_CalcTangentSpace | aiProcess_FlipUVs);
	AiModel::directory = pFile.substr(0, pFile.find_last_of('/'));

	//Note: This only returns the first Mesh. For multiple meshes, will need to fix this in the future
	AiModel::data = AiModel::LoadData(scene->mMeshes[0]);
}
/*
	Extract the mesh data from an AiMesh
	@param mesh			aiMesh of the model
	@return MeshData	MeshData of the mesh	
*/

MeshData AiModel::LoadData(aiMesh * mesh)
{
	float *vertexArray;
	float *normalArray;
	float *uvArray;
	unsigned int *indexArray;

	unsigned int numVerts;
	unsigned int indexCount = 0;

	numVerts = mesh->mNumFaces * 3;

	vertexArray = new float[mesh->mNumFaces * 3 * 3];
	normalArray = new float[mesh->mNumFaces * 3 * 3];
	uvArray = new float[mesh->mNumFaces * 3 * 2];
	indexArray = new unsigned int[mesh->mNumFaces * 3];
	indexCount = mesh->mNumFaces;

	for (unsigned int i = 0; i<mesh->mNumFaces; i++)
	{
		const aiFace& face = mesh->mFaces[i];

		for (int j = 0; j<3; j++)
		{
			aiVector3D uv = mesh->mTextureCoords[0][face.mIndices[j]];
			std::cout << "UV: " << std::endl;
			std::cout << uv.x << " " << uv.y << " " << uv.z << std::endl;
			memcpy(uvArray, &uv, sizeof(float) * 2);
			uvArray += 2;

			aiVector3D normal = mesh->mNormals[face.mIndices[j]];
			memcpy(normalArray, &normal, sizeof(float) * 3);
			normalArray += 3;

			aiVector3D pos = mesh->mVertices[face.mIndices[j]];
			std::cout << "VertexPos: " << std::endl;
			std::cout << pos.x << " " << pos.y << " " << pos.z << std::endl;
			memcpy(vertexArray, &pos, sizeof(float) * 3);
			vertexArray += 3;
		}
		std::cout << "Indices: " << std::endl;
		for (int j = 0; j < face.mNumIndices; j++) {
			indexArray[i + j] = face.mIndices[j];
			
			std::cout << indexArray[i + j] << ", ";
		}
		std::cout << "Indices: " << std::endl;
			
	}

	uvArray -= mesh->mNumFaces * 3 * 2;
	normalArray -= mesh->mNumFaces * 3 * 3;
	vertexArray -= mesh->mNumFaces * 3 * 3;

	return MeshData{};
}

