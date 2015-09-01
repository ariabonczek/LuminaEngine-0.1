#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "../Config.hpp"
#include "../Math/Math.hpp"

#include "Component.hpp"

NS_BEGIN

/// <summary>
/// Component which handles GameObject position, rotation, scale, etc.
/// </summary>
class Transform : public Component
{
public:
	Transform();
	~Transform();

	void Initialize();

	void Translate(Vector3 v);
	void Rotate(Quaternion q);

	void SetLocalPosition(float x, float y, float z);
	void SetLocalPosition(Vector3 position);

	void SetLocalRotation(Quaternion rotation);

	void SetLocalScale(float x, float y, float z);
	void SetLocalScale(Vector3 scale);

	Vector3 GetLocalPosition()const;
	Quaternion GetLocalRotation()const;
	Vector3 GetLocalScale()const;
	Vector3 GetEulerAngles()const;

	Vector3 GetWorldPosition();
	Quaternion GetWorldRotation();
	Vector3 GetWorldScale();

	Matrix GetWorldMatrix()const;
	Matrix GetWorldInverseTranspose();

	Vector3 GetForward()const;
	Vector3 GetUp()const;
	Vector3 GetRight()const;

	void SetParent(Transform* transform);
	void AddChild(Transform* transform);

	Transform* GetParent();
	std::vector<Transform*> GetChildren();

private:
	void UpdateWorldMatrix();
	/// <summary>
	/// Returns true if the object has no parents
	/// </summary>
	bool IsBatman()const;

	Transform* parent;
	std::vector<Transform*> children;

	Vector3 localPosition;
	Vector3 localScale;
	Quaternion localRotation;
	Vector3 eulerAngles;

	Vector3 forward;
	Vector3 up;
	Vector3 right;

	Matrix worldCache;
};

NS_END

#endif