#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "../Config.hpp"

NS_BEGIN

struct Matrix;
typedef unsigned int uint;

struct Vector2
{
	float x, y;

	//////////////////
	// Constructors //
	//////////////////
	Vector2();
	Vector2(float value);
	Vector2(float x, float y);

	static Vector2 Zero;
	static Vector2 One;

	//////////////////////
	// Member Functions //
	//////////////////////
	float Length();
	float LengthSquared();
	void Normalize();
	Vector2 Normalized();

	///////////////
	// Operators //
	///////////////
	Vector2 operator-();
	Vector2 operator+(const Vector2& v);
	void operator+=(const Vector2& v);
	void operator-=(const Vector2& v);
	Vector2 operator-(const Vector2& v);
	Vector2 operator*(const float& s);
	Vector2 operator/(const float& d);
	Vector2 operator/(const Vector2& v);
	bool	operator==(const Vector2& v);
	bool	operator!=(const Vector2& v);
	float   operator[](const int index);

	//////////////////////
	// Static Functions //
	//////////////////////

	/// <summary>
	/// Returns a vector using component-wise addition
	/// </summary>
	static Vector2 Add(Vector2 v1, Vector2 v2);

	/// <summary>
	/// Returns a clamped version of vector v
	/// </summary>
	static Vector2 Clamp(Vector2 v, Vector2 min, Vector2 max);

	/// <summary>
	/// Returns the distance from v1 to v2
	/// </summary>
	static float   Distance(Vector2 v1, Vector2 v2);

	/// <summary>
	/// Returns the distance squared from v1 to v2
	/// </summary>
	static float   DistanceSquared(Vector2 v1, Vector2 v2);

	/// <summary>
	/// Returns a vector using component-wise division
	/// </summary>
	static Vector2 Divide(Vector2 v1, Vector2 v2);

	/// <summary>
	/// Returns a vector with each term divided by d
	/// </summary>
	static Vector2 Divide(Vector2 v, float d);

	/// <summary>
	/// Returns the dot product of two vectors
	/// </summary>
	static float   Dot(Vector2 v1, Vector2 v2);

	/// <summary>
	/// Returns the maximum values of two vectors
	/// </summary>
	static Vector2 Max(Vector2 v1, Vector2 v2);

	/// <summary>
	/// Returns the minimum values of two vectors
	/// </summary>
	static Vector2 Min(Vector2 v1, Vector2 v2);

	/// <summary>
	/// Returns a vector using component-wise multiplication
	/// </summary>
	static Vector2 Multiply(Vector2 v1, Vector2 v2);

	/// <summary>
	/// Returns a vector scaled by s
	/// </summary>
	static Vector2 Multiply(Vector2 v, float s);

	/// <summary>
	/// Returns the negative of vector v
	/// </summary>
	static Vector2 Negate(Vector2 v);

	/// <summary>
	/// Returns a normalized version of vector v
	/// </summary>
	static Vector2 Normalized(Vector2 v);

	/// <summary>
	/// Returns a vector reflected across a normal
	/// </summary>
	static Vector2 Reflect(Vector2 v, Vector2 normal);

	/// <summary>
	/// Returns a vector using component-wise subtraction
	/// </summary>
	static Vector2 Subtract(Vector2 v1, Vector2 v2);

	// TODO: Transform functions with Matrices and Quaternions
};

struct Vector3
{
	float x, y, z;

	//////////////////
	// Constructors //
	//////////////////
	Vector3();
	Vector3(float value);
	Vector3(Vector2 v2, float z);
	Vector3(float x, float y, float z);

	static Vector3 Zero;
	static Vector3 One;
	static Vector3 Right;
	static Vector3 Up;
	static Vector3 Forward;

	//////////////////////
	// Member Functions //
	//////////////////////
	float Length();
	float LengthSquared();

	// NOTE THE DIFFERENCE (hint: its the d.)
	void Normalize();
	Vector3 Normalized();

	void SetMagnitude(float mag);

	///////////////
	// Operators //
	///////////////
	Vector3 operator-();
	Vector3 operator+(const Vector3& v);
	Vector3 operator-(const Vector3& v);
	Vector3 operator*(const Matrix& m);
	Vector3 operator/(const float& d);
	Vector3 operator/(const Vector3& v);
	bool	operator==(const Vector3& v);
	bool	operator!=(const Vector3& v);
	float   operator[](const int index);

	//////////////////////
	// Static Functions //
	//////////////////////

	/// <summary>
	/// Returns a vector using component-wise addition
	/// </summary>
	static Vector3 Add(Vector3 v1, Vector3 v2);

	/// <summary>
	/// Returns a clamped version of vector v
	/// </summary>
	static Vector3 Clamp(Vector3 v, Vector3 min, Vector3 max);

	/// <summary>
	/// Returns a vector that is perpendicular to both v1 and v2
	/// </summary>
	static Vector3 Cross(Vector3 v1, Vector3 v2);

	/// <summary>
	/// Returns the distance from v1 to v2
	/// </summary>
	static float   Distance(Vector3 v1, Vector3 v2);

	/// <summary>
	/// Returns the distance squared from v1 to v2
	/// </summary>
	static float   DistanceSquared(Vector3 v1, Vector3 v2);

	/// <summary>
	/// Returns a vector using component-wise division
	/// </summary>
	static Vector3 Divide(Vector3 v1, Vector3 v2);

	/// <summary>
	/// Returns a vector with each term divided by d
	/// </summary>
	static Vector3 Divide(Vector3 v, float d);

	/// <summary>
	/// Returns the dot product of two vectors
	/// </summary>
	static float   Dot(Vector3 v1, Vector3 v2);

	/// <summary>
	/// Returns the maximum values of two vectors
	/// </summary>
	static Vector3 Max(Vector3 v1, Vector3 v2);

	/// <summary>
	/// Returns the minimum values of two vectors
	/// </summary>
	static Vector3 Min(Vector3 v1, Vector3 v2);

	/// <summary>
	/// Returns a vector using component-wise multiplication
	/// </summary>
	static Vector3 Multiply(Vector3 v1, Vector3 v2);

	/// <summary>
	/// Returns a vector scaled by s
	/// </summary>
	static Vector3 Multiply(Vector3 v, float s);

	/// <summary>
	/// Returns the negative of vector v
	/// </summary>
	static Vector3 Negate(Vector3 v);

	/// <summary>
	/// Returns a normalized version of vector v
	/// </summary>
	static Vector3 Normalize(Vector3 v);

	/// <summary>
	/// Returns a vector reflected across a normal
	/// </summary>
	static Vector3 Reflect(Vector3 v, Vector3 normal);

	/// <summary>
	/// Returns a vector using component-wise subtraction
	/// </summary>
	static Vector3 Subtract(Vector3 v1, Vector3 v2);

	// TODO: Transform functions with Matrices and Quaternions
};

struct Vector4
{
	float x, y, z, w;

	//////////////////
	// Constructors //
	//////////////////
	Vector4();
	Vector4(float value);
	Vector4(Vector3 v3, float w);
	Vector4(Vector2 v2, float z, float w);
	Vector4(float x, float y, float z, float w);

	static Vector4 Zero;
	static Vector4 One;

	//////////////////////
	// Member Functions //
	//////////////////////
	float Length();
	float LengthSquared();
	void Normalize();
	Vector4 Normalized();

	///////////////
	// Operators //
	///////////////
	Vector4 operator-();
	Vector4 operator+(const Vector4& v);
	Vector4 operator-(const Vector4& v);
	Vector4 operator/(const float& d);
	Vector4 operator/(const Vector4& v);
	bool	operator==(const Vector4& v);
	bool	operator!=(const Vector4& v);
	float   operator[](const int index);

	//////////////////////
	// Static Functions //
	//////////////////////

	/// <summary>
	/// Returns a vector using component-wise addition
	/// </summary>
	static Vector4 Add(Vector4 v1, Vector4 v2);

	/// <summary>
	/// Returns a clamped version of vector v
	/// </summary>
	static Vector4 Clamp(Vector4 v, Vector4 min, Vector4 max);

	/// <summary>
	/// Returns the distance from v1 to v2
	/// </summary>
	static float   Distance(Vector4 v1, Vector4 v2);

	/// <summary>
	/// Returns the distance squared from v1 to v2
	/// </summary>
	static float   DistanceSquared(Vector4 v1, Vector4 v2);

	/// <summary>
	/// Returns a vector using component-wise division
	/// </summary>
	static Vector4 Divide(Vector4 v1, Vector4 v2);

	/// <summary>
	/// Returns a vector with each term divided by d
	/// </summary>
	static Vector4 Divide(Vector4 v, float d);

	/// <summary>
	/// Returns the dot product of two vectors
	/// </summary>
	static float   Dot(Vector4 v1, Vector4 v2);

	/// <summary>
	/// Returns the maximum values of two vectors
	/// </summary>
	static Vector4 Max(Vector4 v1, Vector4 v2);

	/// <summary>
	/// Returns the minimum values of two vectors
	/// </summary>
	static Vector4 Min(Vector4 v1, Vector4 v2);

	/// <summary>
	/// Returns a vector using component-wise multiplication
	/// </summary>
	static Vector4 Multiply(Vector4 v1, Vector4 v2);

	/// <summary>
	/// Returns a vector scaled by s
	/// </summary>
	static Vector4 Multiply(Vector4 v, float s);

	/// <summary>
	/// Returns the negative of vector v
	/// </summary>
	static Vector4 Negate(Vector4 v);

	/// <summary>
	/// Returns a normalized version of vector v
	/// </summary>
	static Vector4 Normalized(Vector4 v);

	/// <summary>
	/// Returns a vector reflected across a normal
	/// </summary>
	static Vector4 Reflect(Vector4 v, Vector4 normal);

	/// <summary>
	/// Returns a vector using component-wise subtraction
	/// </summary>
	static Vector4 Subtract(Vector4 v1, Vector4 v2);

	// TODO: Transform functions with Matrices and Quaternions
};

// TODO: Finish these
Vector3 operator+(const Vector3& l, const Vector3& r);
Vector3 operator*(const Vector3& l, const Vector3& r);
Vector3 operator*(const Vector3& l, const Matrix& r);

NS_END
#endif