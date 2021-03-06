#include "Plane.hpp"

#include "../../Graphics/MeshRenderer.hpp"
#include "../../Graphics/Material.hpp"
#include "../../Utility/ResourceManager.hpp"

NS_BEGIN

Plane::Plane():
GameObject()
{
	AddComponent<MeshRenderer>(new MeshRenderer(ResourceManager::CreatePrimitive(PlaneMesh)));
}

Plane::~Plane()
{

}

void Plane::Update()
{

}

NS_END