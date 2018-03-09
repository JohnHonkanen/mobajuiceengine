#include "render\LightManager.h"
#include "components\Light.h"
namespace Engine
{
	LightManager *LightManager::manager = nullptr;

	LightManager * LightManager::Get()
	{
		if (manager == nullptr)
		{
			manager = new LightManager();
		}

		return manager;
	}

	void LightManager::AddLight(LightType type, Light * light)
	{
		switch (type)
		{
		case Engine::POINT_LIGHT:
			light->SetSlot(point.size());
			point.push_back(light);
			break;
		case Engine::SPOTLIGHT:
			light->SetSlot(spotlight.size());
			spotlight.push_back(light);
			break;
		case Engine::DIRECTIONAL_LIGHT:
			light->SetSlot(directional.size());
			directional.push_back(light);
			break;
		default:
			break;
		}
	}

	std::vector<Light *> LightManager::GetLights(LightType type) const
	{
		switch (type)
		{
		case Engine::POINT_LIGHT:
			return std::vector<Light *>(point.begin(), point.end());
			break;
		case Engine::SPOTLIGHT:
			return std::vector<Light *>(spotlight.begin(), spotlight.end());
			break;
		case Engine::DIRECTIONAL_LIGHT:
			return std::vector<Light *>(directional.begin(), directional.end());
			break;
		default:
			return std::vector<Light *>();
			break;
		}
	}

}
