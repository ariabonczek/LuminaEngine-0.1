#include "GameObject.hpp"

#include "Component.hpp"
#include "Transform.hpp"
#include "../Utility/Resource.hpp"
#include "../Graphics/Material.hpp"
#include "../Graphics/MeshRenderer.hpp"
#include "../Graphics/Camera.hpp"
#include "../Graphics/Lighting/Lighting.hpp"

NS_BEGIN

GameObject::GameObject(std::string name):
isStatic(false), 
isDestroyed(false),
name(name)
{
	InitializeComponentMap();
}

GameObject::~GameObject()
{
	if (!isDestroyed)
		Destroy();
}

void GameObject::Initialize()
{
	for (std::map<std::string, Component*>::iterator it = components.begin(); it != components.end(); ++it)
	{
		if (it->second)
			it->second->Initialize();
	}
}

template<class T>
T* GameObject::GetComponent()
{
	// TODO: Messy
	const char* n = typeid(T).name();
	std::string name = n;
	uint index = (uint)name.find_last_of(':');

	name = name.substr(index + 1, name.length() - 1);

	return (T*)(components[name]);
}

template Component* GameObject::GetComponent<Component>();
template Light* GameObject::GetComponent<Light>();
template Transform* GameObject::GetComponent<Transform>();
template MeshRenderer* GameObject::GetComponent<MeshRenderer>();
template Camera* GameObject::GetComponent<Camera>();

template<class T>
void GameObject::AddComponent(T* component)
{
	// TODO: Messy
	const char* n = typeid(T).name();
	std::string name = n;
	uint index = (uint)name.find_last_of(':');

	name = name.substr(index + 1, name.length() - 1);

	if (components.find(name) == components.end())
	{
#ifdef DEBUG
		Debug::LogError("[GameObject] Attempt made to add a non-component");
#endif
		return;
	}

	if (components[name])
	{
#ifdef DEBUG
		Debug::LogError("[GameObject] Attempt made to add a second of an already existing component");
#endif
		return;
	}

	Component* c = (Component*)component;
	
	if (!c->OnAddToGameObject(this))
	{
#if DEBUG
		Debug::LogError("[GameObject] That component already has a GameObject!");
#endif
		return;
	}

	components[name] = (Component*)(component);
}

template void GameObject::AddComponent<Component>(Component* component);
template void GameObject::AddComponent<Light>(Light* light);
template void GameObject::AddComponent<DirectionalLight>(DirectionalLight* dLight);
template void GameObject::AddComponent<SpotLight>(SpotLight* sLight);
template void GameObject::AddComponent<PointLight>(PointLight* pLight);
template void GameObject::AddComponent<MeshRenderer>(MeshRenderer* meshRenderer);
template void GameObject::AddComponent<Camera>(Camera* camera);

void GameObject::Destroy()
{
	for (std::map<std::string, Component*>::iterator i = components.begin(); i != components.end(); i++)
	{
		delete i->second;
	}
	components.clear();

	isDestroyed = true;
}

void GameObject::Update()
{

}

void GameObject::Render()
{
	// TODO: Only call Render on objects that are renderable
	if (!components["MeshRenderer"])
	{
		return;
	}
	MeshRenderer* mr = GetComponent<MeshRenderer>();
	mr->BindMesh();
	mr->Draw();
}

void GameObject::SetIsStatic(bool val)
{
	isStatic = true;
}

bool GameObject::GetIsStatic()const
{
	return isStatic;
}

Transform* GameObject::GetTransform()
{
	return (Transform*)(components["Transform"]);
}

std::string GameObject::GetName()const
{
	return name;
}

void GameObject::InitializeComponentMap()
{
	components["Transform"] = new Transform();
	components["Transform"]->OnAddToGameObject(this);

	components["MeshRenderer"] = 0;
	components["Camera"] = 0;
	components["Light"] = 0;
}

void GameObject::OnPositionChange()
{

}

NS_END