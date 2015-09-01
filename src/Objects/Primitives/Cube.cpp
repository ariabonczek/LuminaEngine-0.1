#include "Cube.hpp"

#include "../../Graphics/MeshRenderer.hpp"
#include "../../Graphics/Material.hpp"
#include "../../Utility/ResourceManager.hpp"

NS_BEGIN

Cube::Cube() : 
GameObject()
{
	AddComponent<MeshRenderer>(new MeshRenderer(ResourceManager::CreatePrimitive(CubeMesh)));
}

Cube::~Cube()
{

}

void Cube::Update()
{

}

NS_END