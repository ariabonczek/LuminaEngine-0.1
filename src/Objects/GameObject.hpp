#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "../Config.hpp"

NS_BEGIN

class Component;

/// <summary>
/// 
/// </summary>
class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	// TODO: Call initialize on all GameObjects

	/// <summary>
	/// Initialize called on all GameObjects AFTER LoadResources
	/// </summary>
	void Initialize();

	/// <summary>
	/// Returns a component of type T if it exists and null if it does not
	/// </summary>
	template<class T>
	T* GetComponent();

	/// <summary>
	/// Adds a component to the object if one doesn't exist already
	/// </summary>
	template<class T>
	void AddComponent(T* comp);

	/// <summary>
	/// Safely handles the destruction of a GameObject, freeing memory
	/// </summary>
	void Destroy();

	// TODO: When command buffers are set up, will have to edit this
	virtual void Update();

	virtual void Render();

	#pragma region Sets
	/// <summary>
	/// Sets the GameObject as static, enabling it for static batching
	/// </summary>
	void SetIsStatic(bool val = true);
	#pragma endregion

	#pragma region Gets
	/// <summary>
	/// Returns whether or not an object is static
	/// </summary>
	bool GetIsStatic()const;

	GameObject* GetParent()const;
	std::vector<GameObject*> GetChildren()const;
	#pragma endregion

protected:
	void InitializeComponentMap();
	void OnPositionChange();

	GameObject* parent;
	std::vector<GameObject*> children;
	
	std::map<std::string, Component*> components;

	bool isStatic;
	bool isDestroyed;
};

NS_END

#endif