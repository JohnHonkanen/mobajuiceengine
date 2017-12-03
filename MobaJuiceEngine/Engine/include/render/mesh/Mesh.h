#pragma once
#include <GL\glew.h>
#include <string>
#include <vector>
namespace Engine {
	class Mesh {
	public:
		virtual void Render() = 0;
		virtual std::string GetShader() = 0;
		virtual std::vector<unsigned int> getID() = 0;
	};
}