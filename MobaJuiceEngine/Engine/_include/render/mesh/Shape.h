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
		void setShaderProgram(string program) {
			material[0].shader = program;
		}
	protected:
		vector<MeshData> data;
		vector<Material> material;
	};
}