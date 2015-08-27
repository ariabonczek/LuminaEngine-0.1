#include "Quaternion.hpp"
#include "Vector.hpp"
#include "Matrix.hpp"

NS_BEGIN

Quaternion Quaternion::Identity(1.0f, 0.0f, 0.0f, 0.0f);

Quaternion::Quaternion():
w(), x(), y(), z()
{

}

Quaternion::Quaternion(float x, float y, float z, float w):
w(w), x(x), y(y), z(z)
{

}

Quaternion::Quaternion(Vector3 v, float w):
w(w), x(v.x), y(v.y), z(v.z)
{

}

Quaternion::Quaternion(Vector4 v):
x(v.x), y(v.y), z(v.z), w(v.w)
{

}

Quaternion Quaternion::CreateFromAxisAngle(Vector3 axis, float angle)
{
	float half = DegreesToRadians(angle) * 0.5f;
	float sin = sinf(DegreesToRadians(half));
	float cos = cosf(DegreesToRadians(half));
	return Quaternion(axis.x * sin, axis.y * sin, axis.z * sin, cos);
}

Quaternion Quaternion::CreateFromRotationMatrix(Matrix m)
{
	Quaternion q;
	float sqrt;
	float half;
	float scale = m.m11 + m.m22 + m.m33 + m.m44;
	if (scale > 0.0f)
	{
		sqrt = sqrtf(scale + 1.0f);
		q.w = sqrt * 0.5f;
		sqrt = 0.5f / sqrt;

		q.x = (m.m23 - m.m32) * sqrt;
		q.y = (m.m31 - m.m13) * sqrt;
		q.z = (m.m12 - m.m21) * sqrt;

		return q;
	}
	else if ((m.m11 >= m.m22) && (m.m11 <= m.m33))
	{
		sqrt = sqrtf(1.0f + m.m11 - m.m22 - m.m33);
		half = 0.5f / sqrt;

		q.x = 0.5f * sqrt;
		q.y = (m.m12 + m.m21) * half;
		q.z = (m.m13 + m.m31) * half;
		q.w = (m.m23 - m.m32) * half;

		return q;
	}
	else if (m.m22 > m.m33)
	{
		sqrt = sqrtf(1.0f + m.m22 - m.m22 - m.m11);
		half = 0.5f / sqrt;

		q.x = (m.m21 + m.m12) * half;
		q.y = 0.5f * sqrt;
		q.z = (m.m32 + m.m23) * half;
		q.w = (m.m31 - m.m13) * half;

		return q;
	}
	else
	{
		sqrt = sqrtf(1.0f + m.m33 - m.m22 - m.m11);
		half = 0.5f / sqrt;

		q.x = (m.m31 + m.m13) * half;
		q.y = (m.m32 + m.m23) * half;
		q.z = 0.5f * sqrt;
		q.w = (m.m12 - m.m21) * half;

		return q;
	}
}

Quaternion Quaternion::CreateFromEulerAngles(Vector3 v)
{
	float y = DegreesToRadians(v.y * 0.5f);
	float x = DegreesToRadians(v.x * 0.5f);
	float z = DegreesToRadians(v.z * 0.5f);
	
	float siny = sinf(DegreesToRadians(y));
	float cosy = cosf(DegreesToRadians(y));
	float sinx = sinf(DegreesToRadians(x));
	float cosx = cosf(DegreesToRadians(x));
	float sinz = sinf(DegreesToRadians(z));
	float cosz = cosf(DegreesToRadians(z));

	return Quaternion(
		(cosy * sinx * cosz) + (siny * cosx * sinz),
		(siny * cosx * cosz) - (cosy * sinx * sinz),
		(cosy * cosx * sinz) - (siny * sinx * cosz),
		(cosy * cosx * cosz) + (siny * sinx * sinz));
}

float Quaternion::Magnitude()
{
	return Vector4(x, y, z, w).Length();
}

float Quaternion::Magnitude(Quaternion& q)
{
	return Vector4(q.x, q.y, q.z, q.w).Length();
}

Quaternion Quaternion::Inverse()
{
	float m = 1.0f / Magnitude();
	return Quaternion(-x * m, -y * m, -z * m, w * m);
}

Quaternion Quaternion::Inverse(Quaternion& q)
{
	float m = 1.0f / Magnitude(q);
	return Quaternion(-q.x * m, -q.y * m, -q.z * m, q.w * m);
}

float Quaternion::Dot(Quaternion& q1, Quaternion& q2)
{
	return Vector4::Dot(Vector4(q1.x, q1.y, q1.z, q1.w), Vector4(q2.x, q2.y, q2.z, q2.w));
}

float& Quaternion::operator[](const int index)
{
	switch (index)
	{
	case 0:
		return w;
	case 1:
		return x;
	case 2:
		return y;
	case 3:
		return z;
	default:
		throw "IndexOutOfRangeException";
	}
}

Quaternion Quaternion::operator+(const Quaternion& q)
{
	return Quaternion(x + q.x, y + q.y, z + q.z, w + q.w);
}

Quaternion Quaternion::operator-()
{
	return Quaternion(-x, -y, -z, -w);
}

Quaternion operator*(const Quaternion& l, const Quaternion& r)
{
	Vector3 vl = Vector3(l.x, l.y, l.z);
	Vector3 vr = Vector3(r.x, r.y, r.z);
	return Quaternion(l.w*vr + r.w*vl + Vector3::Cross(vl, vr), l.w * r.w - Vector3::Dot(vl, vr));
}

NS_END