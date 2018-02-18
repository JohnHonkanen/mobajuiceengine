#pragma once
#include <GL\glew.h>
#include <string>
#include <vector>
#include "render\Material.h"
namespace Engine {
	class Mesh {
	public:
		virtual void Render(Material *material) = 0;
		virtual std::string GetShader() = 0;
		virtual std::vector<unsigned int> getID() = 0;
		virtual Material *GetMaterial() = 0;
	};
}