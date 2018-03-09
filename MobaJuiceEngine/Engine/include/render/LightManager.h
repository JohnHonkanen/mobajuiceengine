#pragma once
#include <vector>

namespace Engine
{
	enum LightType
	{
		POINT_LIGHT,
		SPOTLIGHT,
		DIRECTIONAL_LIGHT
	};

	class LightManager
	{
	public:
		static LightManager * Get();

		void AddLight(LightType  type, class Light *light);
		std::vector<class Light *> GetLights(LightType type) const;
	private:
		static LightManager * manager;
		LightManager() {};

		std::vector<class Light *> point;
		std::vector<class Light *> directional;
		std::vector<class Light *> spotlight;
	};
}
