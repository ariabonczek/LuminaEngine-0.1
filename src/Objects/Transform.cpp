#include "Transform.hpp"

#include "GameObject.hpp"
#include "../Graphics/Camera.hpp"

NS_BEGIN

Transform::Transform() :
localPosition(0.0f, 0.0f, 0.0f),
localRotation(0.0f, 0.0f, 0.0f),
localScale(1.0f, 1.0f, 1.0f),
forward(0.0f, 0.0f, 1.0f),
up(0.0f, 1.0f, 0.0f),
right(1.0f, 0.0f, 0.0f)
{}

Transform::~Transform()
{}

void Transform::Initialize()
{
	UpdateWorldMatrix();
}

void Transform::Translate(Vector3 v)
{
	localPosition = localPosition + v;
	UpdateWorldMatrix();
	if (Camera* c = gameObject->GetComponent<Camera>()){ c->UpdateViewMatrix(); }
}

void Transform::Rotate(Vector3 rotation)
{
	Matrix r = Matrix::CreateRotation(rotation);

	localRotation = localRotation + rotation;
	UpdateWorldMatrix();
	if (Camera* c = gameObject->GetComponent<Camera>()){ c->UpdateViewMatrix(); }
}

void Transform::Rotate(Vector3 axis, float angle)
{
	Matrix m = Matrix::CreateRotationByAxisAngle(axis, angle);

	Vector3 delta = Matrix::RotationToEuler(m);
	localRotation = localRotation + delta;

	UpdateWorldMatrix();
	if (Camera* c = gameObject->GetComponent<Camera>()){ c->UpdateViewMatrix(); }
}

void Transform::SetLocalPosition(float x, float y, float z){ localPosition = Vector3(x, y, z); UpdateWorldMatrix(); if (Camera* c = gameObject->GetComponent<Camera>()){ c->UpdateViewMatrix(); } }
void Transform::SetLocalPosition(Vector3 position){ localPosition = position; }
void Transform::SetLocalRotation(float x, float y, float z){ localRotation = Vector3(x, y, z); UpdateWorldMatrix(); if (Camera* c = gameObject->GetComponent<Camera>()){ c->UpdateViewMatrix(); } }
void Transform::SetLocalRotation(Vector3 rotation){ localRotation = rotation; }
void Transform::SetLocalScale(float x, float y, float z) { localScale = Vector3(x, y, z); UpdateWorldMatrix(); if (Camera* c = gameObject->GetComponent<Camera>()){ c->UpdateViewMatrix(); } }
void Transform::SetLocalScale(Vector3 scale){ localScale = scale; }

Vector3 Transform::GetLocalPosition()const{ return localPosition; }
Vector3 Transform::GetLocalRotation()const{ return localRotation; }
Vector3 Transform::GetLocalScale()const {return localScale; }

Vector3 Transform::GetWorldPosition()
{
	if (IsBatman()) return localPosition;
	else
	{
		return localPosition + GetParentTransform()->GetWorldPosition();
	}
}
Vector3 Transform::GetWorldRotation()
{
	if (IsBatman()) return localRotation;
	else
	{
		return localRotation + GetParentTransform()->GetWorldRotation();
	}
}

Vector3 Transform::GetWorldScale()
{
	if (IsBatman()) return localScale;
	else
	{
		return localScale * GetParentTransform()->GetWorldScale();
	} 
}

Matrix Transform::GetWorldMatrix()const
{
	if (IsBatman()) return worldCache;
	else
	{
		return worldCache * GetParentTransform()->GetWorldMatrix();
	}
}

Matrix Transform::GetWorldInverseTranspose()
{
	return Matrix::Transpose(Matrix::Inverse(worldCache));
}

void Transform::UpdateWorldMatrix()
{
	Matrix r, s, t;
	Vector3 worldPosition = GetWorldPosition();
	Vector3 worldRotation = GetWorldRotation();
	Vector3 worldScale = GetWorldScale();

	r = Matrix::CreateRotation(worldRotation);
	s = Matrix::CreateScale(worldScale);
	t = Matrix::CreateTranslation(worldPosition);

	worldCache = t*r*s;

	forward = Vector3::Normalize(Vector3::Forward * r);
	right = Vector3::Normalize(Vector3::Cross(Vector3::Up, forward));
	up = Vector3::Cross(forward, right);
}

bool Transform::IsBatman()const
{
	return !gameObject->GetParent();
}

Transform* Transform::GetParentTransform()const
{
	// Should check IsBatman before calling this
	if (IsBatman()) return 0;
	else
	{
		return gameObject->GetParent()->GetComponent<Transform>();
	}
}

Vector3 Transform::GetForward()const
{
	return forward;
}

Vector3 Transform::GetUp()const
{
	return up;
}

Vector3 Transform::GetRight()const
{
	return right;
}

NS_END