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

	void LightManager::RemoveLight(LightType type, Light * light)
	{
		auto it = FindLight(type, light);

		switch (type)
		{
		case Engine::POINT_LIGHT:
			point.erase(it);
			break;
		case Engine::SPOTLIGHT:
			spotlight.erase(it);
			break;
		case Engine::DIRECTIONAL_LIGHT:
			directional.erase(it);
			break;
		default:
			break;
		}
	}

	std::vector<Light *>::iterator LightManager::FindLight(LightType type, Light * light)
	{
		std::vector<Light *>::iterator it;
		switch (type)
		{
		case Engine::POINT_LIGHT:
			it = find(point.begin(), point.end(), light);
			break;
		case Engine::SPOTLIGHT:
			it = find(spotlight.begin(), spotlight.end(), light);
			break;
		case Engine::DIRECTIONAL_LIGHT:
			it = find(directional.begin(), directional.end(), light);
			break;
		default:
			break;
		}
		return it;
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
