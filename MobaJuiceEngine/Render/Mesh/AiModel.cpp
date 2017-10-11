#include "AiModel.h"
#include <fstream>
#include <iostream>
#include <vector>

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
	std::vector<float> vertexArray;
	std::vector<float> normalArray;
	std::vector<float> uvArray;
	std::vector<unsigned int> indexArray;

	unsigned int numVerts;
	unsigned int indexCount = 0;

	numVerts = mesh->mNumFaces * 3;
	indexCount = mesh->mNumFaces;

	for (unsigned int i = 0; i<mesh->mNumFaces; i++)
	{
		const aiFace& face = mesh->mFaces[i];

		for (int j = 0; j<3; j++)
		{
			/*if (mesh->HasTextureCoords(0)) {
				aiVector3D uv = mesh->mTextureCoords[0][face.mIndices[j]];
				uvArray.push_back(uv.x);
				uvArray.push_back(uv.y);
			}*/
			

			if (mesh->HasNormals()) {
				aiVector3D normal = mesh->mNormals[face.mIndices[j]];
				normalArray.push_back(normal.x);
				normalArray.push_back(normal.y);
				normalArray.push_back(normal.z);
			}
			

			aiVector3D pos = mesh->mVertices[face.mIndices[j]];
			vertexArray.push_back(pos.x);
			vertexArray.push_back(pos.y);
			vertexArray.push_back(pos.z);
		}
		for (int j = 0; j < face.mNumIndices; j++) {
			indexArray.push_back(face.mIndices[j]);
			
		}
			
	}

	MeshData data;
	data.vertexArray = vertexArray;
	data.indices = indexArray;
	data.uvArray = uvArray;
	data.normalArray = normalArray;
	data.numVerts = numVerts;
	data.indexCount = indexArray.size();

	return data;
}

