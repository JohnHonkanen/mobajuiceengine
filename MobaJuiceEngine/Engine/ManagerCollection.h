#pragma once
#include "InputManager.h"
#include "Render\Mesh\OGLMeshManager.h"
#include "Render\ShaderManager.h"
#include "Render\Texture\TextureManager.h"
#include "Render\FontManager.h"

namespace Engine {
	class ManagerCollection{
	public:
		InputManager inputManager;
		OGLMeshManager meshManager;
		TextureManager textureManager;
		ShaderManager shaderManager;
		FontManager fontManager;
	};
}