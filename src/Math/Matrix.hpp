#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "../Config.hpp"

NS_BEGIN

struct Vector2;
struct Vector3;
struct Vector4;
struct Quaternion;

struct Matrix
{
	float m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34, m41, m42, m43, m44;

	//////////////////
	// Constructors //
	//////////////////
	Matrix();
	Matrix(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44);

	//////////////////////
	// Static Instances //
	//////////////////////
	static Matrix Identity;

	//////////////////////
	// Member Functions //
	//////////////////////
	float  Determinant();
	Matrix Transpose();
	Vector3 Right();
	Vector3 Up();
	Vector3 Forward();

	///////////////
	// Operators //
	///////////////
	Matrix operator+(const Matrix& m);
	Matrix operator-(const Matrix& m);
	Matrix operator/(const Matrix& m);
	Matrix operator/(const float& f);
	bool   operator==(const Matrix& m);
	float  operator[](int index);

	//////////////////////
	// Static Functions //
	//////////////////////
	static Matrix Add(Matrix& m1, Matrix& m2);
	static Matrix Subtract(Matrix& m1, Matrix& m2);
	static Matrix CreateFromQuaternion(Quaternion q);
	static Matrix CreateLookAt(Vector3 position, Vector3 target, Vector3 up);
	static Matrix CreateOrthographic(float width, float height, float zNear, float zFar);
	static Matrix CreatePerspective(float width, float height, float zNear, float zFar);
	static Matrix CreatePerspectiveFov(float fov, float aspect, float zNear, float zFar);
	static Matrix CreateRotationByAxisAngle(Vector3 axis, float angle);
	static Matrix CreateRotationX(float angle);
	static Matrix CreateRotationY(float angle);
	static Matrix CreateRotationZ(float angle);
	static Matrix CreateRotation(Vector3 rotation);
	static Matrix CreateScale(float scale);
	static Matrix CreateScale(float x, float y, float z);
	static Matrix CreateScale(Vector3 scale);
	static Matrix CreateTranslation(float x, float y, float z);
	static Matrix CreateTranslation(Vector3 translation);
	static Matrix CreateWorld(Vector3 position, Vector3 forward, Vector3 up);
	static Matrix Inverse(Matrix m);
	static Matrix Transpose(Matrix m);
	static Vector3 RotationToEuler(Matrix m);
private:
	/// <summary>
	/// Returns the determinant of a 3x3 matrix
	/// </summary>
	float DeterminantHelper(float m11, float m12, float m13, float m21, float m22, float m23, float m31, float m32, float m33);
};

Matrix operator*(const Matrix& l, const Matrix& r);

NS_END

#endif