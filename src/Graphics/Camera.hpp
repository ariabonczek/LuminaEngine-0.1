#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../Config.hpp"
#include "../Math/Math.hpp"
#include "../Objects/Component.hpp"

NS_BEGIN

class Transform;

/// <summary>
/// 
/// </summary>
class Camera : public Component
{
public:
	Camera();
	~Camera();

	/// <summary>
	/// 
	/// </summary>
	void Initialize();

	/// <summary>
	/// 
	/// </summary>
	void SetLens(float foxY, float aspec, float zNear, float zFar);

	/// <summary>
	/// 
	/// </summary>
	void LookAt(Vector3 target);

	/// <summary>
	/// 
	/// </summary>
	void UpdateViewMatrix();

	void RotateX(float angle);
	void RotateY(float angle);
	void RotateZ(float angle);

	#pragma region Gets
	Vector3 GetLook()const;
	Vector3 GetRight()const;
	Vector3 GetUp()const;

	float GetNearZ()const;
	float GetFarZ()const;
	float GetAspectRatio()const;
	float GetFovX()const;
	float GetFovY()const;
	float GetNearWidth()const;
	float GetNearHeight()const;
	float GetFarWidth()const;
	float GetFarHeight()const;

	Matrix GetView()const;
	Matrix GetProj()const;
	Matrix GetViewProj()const;
	
	#pragma endregion

private:
	Transform* cachedTransform;

	Vector3 look;
	Vector3 right;
	Vector3 up;
	
	float nearZ;
	float farZ;
	float aspectRatio;
	float fovX;
	float fovY;
	float nearWidth;
	float nearHeight;
	float farWidth;
	float farHeight;

	Matrix view;
	Matrix projection;
	Matrix viewProjection;
};

NS_END


#endif