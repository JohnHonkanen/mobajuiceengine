#include "components\TextureSetter.h"
#include "components\MeshRenderer.h"
#include "core\GameObject.h"
TextureSetter * Engine::TextureSetter::Create(GameObject * obj, string diffuseMap)
{
	MeshRenderer *mr = obj->GetComponent<MeshRenderer>();

	if (mr == nullptr) {
		cout << "MeshRenderer not found" << endl;
		return nullptr;
	}
	TextureSetter * ts = new TextureSetter;
	ts->diffuseMap = diffuseMap;

	obj->AddComponent(ts);

}

void Engine::TextureSetter::Start()
{
	MeshRenderer *mr = gameObject->GetComponent<MeshRenderer>();
	mr->material->diffuseMap = diffuseMap;
}
