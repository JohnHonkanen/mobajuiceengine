#pragma once
#include "InputManager.h"
#include "Render\Mesh\OGLMeshManager.h"
#include "Render\ShaderManager.h"
#include "Render\Texture\TextureManager.h"
#include "render\FontManager.h"
#include "core\GameObjectManager.h"
#include "events\EventManager.h"
#include <cereal\cereal.hpp>


namespace Engine {
	using namespace Events;
	class ManagerCollection{
	public:
		InputManager inputManager;
		OGLMeshManager meshManager;
		TextureManager textureManager;
		ShaderManager shaderManager;
		FontManager fontManager;
		EventManager eventManager;

		GameObjectManager * gameObjectManager;

		template<class Archive>
		void serialize(Archive & ar)
		{
			ar(CEREAL_NVP(inputManager));
		}
	};
}