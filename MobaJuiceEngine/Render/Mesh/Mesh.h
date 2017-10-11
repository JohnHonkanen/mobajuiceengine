#pragma once
#include "../Renderer.h"
class Mesh : public Renderer {
public:
	virtual void Render() = 0;
};