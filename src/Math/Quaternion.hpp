#ifndef QUATERNION_HPP
#define QUATERNION_HPP

#include "../Config.hpp"

NS_BEGIN

struct Vector3;

struct Quaternion
{
	float x, y, z, w;

	Quaternion();
	Quaternion(float x, float y, float z, float w);
	Quaternion(Vector3 v, float w);
	Quaternion(Vector4 v);

	//
	// Static Instances
	//
	static Quaternion Identity;

	//
	// Member Functions
	//
	float Magnitude();
	Quaternion Inverse();

	//
	// Static Functions
	//
	static Quaternion CreateFromAxisAngle(Vector3 axis, float angle);
	static Quaternion CreateFromRotationMatrix(Matrix m);
	static Quaternion CreateFromEulerAngles(Vector3 v);

	static float Magnitude(Quaternion& q);
	static Quaternion Inverse(Quaternion& q);
	static Quaternion Multiply(Quaternion& q1, Quaternion& q2);
	static float Dot(Quaternion& q1, Quaternion& q2);

	Quaternion operator+(const Quaternion& q);
	float& operator[](const int index);
	Quaternion operator-();
};

Quaternion operator*(const Quaternion& l, const Quaternion& r);


NS_END

#endif