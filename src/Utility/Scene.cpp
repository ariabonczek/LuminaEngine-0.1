#include "Scene.hpp"

NS_BEGIN

Scene::Scene()
{}

Scene::~Scene()
{}

void Scene::AddObject(GameObject* gameObject)
{
	// Think about this one: pointer component will be stored separately from object AND with it
	if(Light* l = gameObject->GetComponent<Light>())
		lights.push_back(l);

	objs.push_back(gameObject);
}

NS_END