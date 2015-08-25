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
	void Rotate(Vector3 rotation);
	void Rotate(Vector3 axis, float angle);

	void SetLocalPosition(float x, float y, float z);
	void SetLocalPosition(Vector3 position);

	void SetLocalRotation(float x, float y, float z);
	void SetLocalRotation(Vector3 rotation);

	void SetLocalScale(float x, float y, float z);
	void SetLocalScale(Vector3 scale);

	Vector3 GetLocalPosition()const;
	Vector3 GetLocalRotation()const;
	Vector3 GetLocalScale()const;

	Vector3 GetWorldPosition();
	Vector3 GetWorldRotation();
	Vector3 GetWorldScale();

	Matrix GetWorldMatrix()const;
	Matrix GetWorldInverseTranspose();

	Vector3 GetForward()const;
	Vector3 GetUp()const;
	Vector3 GetRight()const;

private:
	void UpdateWorldMatrix();
	/// <summary>
	/// Returns true if the object has no parents
	/// </summary>
	bool IsBatman()const;

	Transform* GetParentTransform()const;

	Vector3 localPosition;
	Vector3 localRotation;
	Vector3 localScale;

	Vector3 forward;
	Vector3 up;
	Vector3 right;

	Matrix worldCache;
};

NS_END

#endif