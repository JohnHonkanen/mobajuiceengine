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

	std::vector<Light*> LightManager::GetLight(LightType type) const
	{
		switch (type)
		{
		case Engine::POINT_LIGHT:
			return point;
			break;
		case Engine::SPOTLIGHT:
			return spotlight;
			break;
		case Engine::DIRECTIONAL_LIGHT:
			return directional;
			break;
		default:
			break;
		}
	}

}
