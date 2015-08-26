#include "Camera.hpp"

#include "../Objects/GameObject.hpp"
#include "../Objects/Transform.hpp"
#include "GraphicsDevice.hpp"

NS_BEGIN

Camera::Camera():
Component()
{

}	

Camera::~Camera()
{}

void Camera::Initialize()
{
	right = Vector3::Right;
	up = Vector3::Up;
	look = Vector3::Forward;

	cachedTransform = gameObject->GetComponent<Transform>();
	SetLens(0.25f * 3.1415926535f, GraphicsDevice::GetAspectRatio(), 0.1f, 200.0f);
	
	UpdateViewMatrix();
}

Vector3 Camera::GetLook()const
{
	return look;
}
Vector3 Camera::GetRight()const
{
	return right;
}
Vector3 Camera::GetUp()const
{
	return up;
}
float Camera::GetNearZ()const
{
	return nearZ;
}
float Camera::GetFarZ()const
{
	return farZ;
}
float Camera::GetAspectRatio()const
{
	return aspectRatio;
}
float Camera::GetFovX()const
{
	return fovX;
}
float Camera::GetFovY()const
{
	return fovY;
}
float Camera::GetNearWidth()const
{
	return nearWidth;
}
float Camera::GetNearHeight()const
{
	return nearHeight;
}
float Camera::GetFarWidth()const
{
	return farWidth;
}
float Camera::GetFarHeight()const
{
	return farHeight;
}
Matrix Camera::GetView()const
{
	return view;
}
Matrix Camera::GetProj()const
{
	return projection;
}
Matrix Camera::GetViewProj()const
{
	return viewProjection;
}

void Camera::SetLens(float fovY, float aspect, float zNear, float zFar)
{
	this->fovY = fovY;
	this->aspectRatio = aspect;
	this->nearZ = zNear;
	this->farZ = zFar;

	nearHeight = 2.0f * nearZ * tanf(0.5f * fovY);
	farHeight = 2.0f * farZ * tanf(0.5f * fovY);

	projection = Matrix::CreatePerspectiveFov(fovY, aspect, zNear, zFar);
}

void Camera::LookAt(Vector3 target)
{
	view = Matrix::CreateLookAt(cachedTransform->GetWorldPosition(), target, Vector3::Up);
	right = view.Right();
	up = view.Up();
	look = view.Forward();
	// TODO: Change the transform rotation based on new view 
}

void Camera::UpdateViewMatrix()
{
	if (cachedTransform)
	{
		// TODO: Investigate possible optimization = check if view is changed before updating it
		// Note: Transform should have GetForward() etc, use those when they work
		Vector3 r = cachedTransform->GetWorldRotation();
		Matrix rm = Matrix::CreateRotation(r);

		right = cachedTransform->GetRight();
		up = cachedTransform->GetUp();
		look = cachedTransform->GetForward();

		Vector3 pos = cachedTransform->GetWorldPosition();

		float x = -Vector3::Dot(pos, right);
		float y = -Vector3::Dot(pos, up);
		float z = -Vector3::Dot(pos, look);

		view = Matrix(
			right.x, up.x, look.x, 0.0f,
			right.y, up.y, look.y, 0.0f,
			right.z, up.z, look.z, 0.0f,
			x, y, z, 1.0f);

		// Cache the viewProjection matrix
		viewProjection = view * projection;
	}
}

void Camera::RotateX(float angle)
{
	Matrix rotation = Matrix::CreateRotationX(angle);

	right = right * rotation;
	look = look * rotation;
	up = up * rotation;
}

void Camera::RotateY(float angle)
{
	Matrix rotation = Matrix::CreateRotationY(angle);

	right = right * rotation;
	look = look * rotation;
	up = up * rotation;

}

void Camera::RotateZ(float angle)
{
	Matrix rotation = Matrix::CreateRotationZ(angle);

	right = right * rotation;
	look = look * rotation;
	up = up * rotation;

}

NS_END