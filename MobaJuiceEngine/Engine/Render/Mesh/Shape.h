#pragma once
#include <vector>
#include "MeshData.h"
#include "../Material.h"

using namespace std;
namespace Engine {
	class Shape {
	public:
		virtual void Init() = 0;
		const vector<MeshData> getMeshData() {
			return data;
		};
		const vector<Material> getMaterials() {
			return material;
		}

	protected:
		vector<MeshData> data;
		vector<Material> material;
	};
}