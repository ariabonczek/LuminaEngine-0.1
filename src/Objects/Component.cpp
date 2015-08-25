#include "Component.hpp"

NS_BEGIN

bool Component::OnAddToGameObject(GameObject* gO)
{
	if (gameObject)
	{
#if DEBUG
		Debug::LogError("[Component] Tried to add an instance of a component to more than one GameObject");
#endif
		return false;
	}
	else
	{
		gameObject = gO;
		return true;
	}
}

GameObject* Component::GetGameObject()
{
	return gameObject;
}

NS_END