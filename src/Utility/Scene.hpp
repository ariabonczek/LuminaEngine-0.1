#ifndef SCENE_HPP
#define SCENE_HPP

#include "../Config.hpp"
#include "../Lumina.hpp"

NS_BEGIN

class GameObject;

/// <summary>
/// Holds information about loading, updating, and rendering game scenes
/// </summary>
class Scene
{
	friend class Renderer;
public:
	Scene();
	virtual ~Scene();

	/// <summary>
	/// Load resources and set up GameObjects here
	/// </summary>
	virtual void LoadResources() = 0;

	/// <summary>
	/// 
	/// </summary>
	virtual void UnloadResources() = 0;

	// TODO: Timer will be static singleton

	/// <summary>
	/// Update game logic here
	/// </summary>
	virtual void Update(float dt) = 0;
protected:
	void AddObject(GameObject* obj);

	Color ambientLight;

	Camera* activeCamera;
	std::vector<GameObject*> objs;
	std::vector<Light*> lights;
};

NS_END

#endif