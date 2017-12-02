#pragma once
#include <GL\glew.h>
#include <string>
namespace Engine {
	class Mesh {
	public:
		virtual void Render() = 0;
		virtual std::string GetShader() = 0;
	};
}