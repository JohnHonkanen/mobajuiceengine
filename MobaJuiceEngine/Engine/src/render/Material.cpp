#include "render\Material.h"

namespace Engine
{
	Material * Material::Copy()
	{
		Material *m = new Material();
		m->shader = shader;
		m->diffuseMap = diffuseMap; //Color Map
		m->normalMap = normalMap;
		m->specularMap = specularMap;
		m->occulusionMap = occulusionMap;
		m->emissionMap = emissionMap;
		m->alphaMap = alphaMap;

		m->color = color;
		m->specular = specular;
		m->diffuse = diffuse;
		m->shininess = shininess;
		return m;
	}
}

