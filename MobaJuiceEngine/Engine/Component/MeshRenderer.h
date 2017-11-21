/*
	Mesh renderer classe used for rendering 3d models
	Dev: B00291253
*/

#pragma once
#include "../Behaviour.h"
#include "../Render/Mesh/Mesh.h"
#include "../Render/Mesh/OGLMeshManager.h"
#include "../Render/Renderer.h"
#include "../Render/OGLShader.h"
#include "../Render/Material.h"
#include <glm\glm.hpp>
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"
#include <cereal\cereal.hpp>
#include <cereal\types\polymorphic.hpp>

namespace Engine {

	class GameObject;
	class MeshRenderer : public Behaviour, Renderer
	{
	public:
		MeshRenderer();
		~MeshRenderer();

		/*
			Sets up the MeshRenderer and its dependicies. Make the gameObject the owner of this component
			@param gameObject	Object that owns this Behaviour
			@param path			Path to model data
			@param shader		Shader used for rendering
			@param manager		Manager used for storing mesh data
			@return				The created mesh renderer object
		*/
		static MeshRenderer *Create(GameObject *gameObject, std::string path, OGLMeshManager *manager);
		void Start();
		void Draw();

		template<class Archive>
		void serialize(Archive & ar)
		{
			ar(CEREAL_NVP(meshPath));
		}

		Material *material;
		std::string meshPath;
		OGLMeshManager * meshManager;
	private:
		Mesh *mesh;
	};
}
using namespace Engine;
//Register camera as a derived class
CEREAL_REGISTER_TYPE(MeshRenderer);

//Bind it to the Behaviour
CEREAL_REGISTER_POLYMORPHIC_RELATION(Behaviour, MeshRenderer);