#pragma once
#include "MeshData.h"
#include "../Material.h"
namespace Engine {
	class Shape {
	public:
		virtual void Init() = 0;
		const MeshData getMeshData() {
			return data;
		};

		Material material;
	protected:
		MeshData data;
	};
}