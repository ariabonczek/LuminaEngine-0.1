#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "../Config.hpp"

NS_BEGIN

class GameObject;

/// <summary>
/// 
/// </summary>
class Component
{
public:
	virtual void Initialize() = 0;

	bool OnAddToGameObject(GameObject* gameObject);

	// TODO: This doesn't encapsulate anything, maybe rework?

	GameObject* GetGameObject();
protected:
	// The GameObject this component is attached to
	GameObject* gameObject;
};

NS_END

#endif