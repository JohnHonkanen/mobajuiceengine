#pragma once
#include "MeshData.h"
class Shape {
public:
	virtual void Init() = 0;
	const MeshData getMeshData() {
		return data;
	};
protected:
	MeshData data;
};