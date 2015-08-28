#include "Scene.hpp"

NS_BEGIN

Scene::Scene():
ambientLight(0.1f, 0.1f, 0.1f, 1.0f)
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