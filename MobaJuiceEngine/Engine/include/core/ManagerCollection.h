#pragma once
#include "InputManager.h"
#include "Render\Mesh\OGLMeshManager.h"
#include "Render\ShaderManager.h"
#include "Render\Texture\TextureManager.h"
#include "render\FontManager.h"
#include "core\GameObjectManager.h"
#include <cereal\cereal.hpp>

namespace Engine {
	class ManagerCollection{
	public:
		InputManager inputManager;
		OGLMeshManager meshManager;
		TextureManager textureManager;
		ShaderManager shaderManager;
		FontManager fontManager;

		GameObjectManager * gameObjectManager;

		template<class Archive>
		void serialize(Archive & ar)
		{
			ar(CEREAL_NVP(inputManager));
		}
	};
}