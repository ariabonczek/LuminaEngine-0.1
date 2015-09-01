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
	axis.Normalize();
	float half = DegreesToRadians(angle) * 0.5f;
	float sin = sinf(half);
	float cos = cosf(half);
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

		return q.Normalized();
	}
	else if ((m.m11 >= m.m22) && (m.m11 <= m.m33))
	{
		sqrt = sqrtf(1.0f + m.m11 - m.m22 - m.m33);
		half = 0.5f / sqrt;

		q.x = 0.5f * sqrt;
		q.y = (m.m12 + m.m21) * half;
		q.z = (m.m13 + m.m31) * half;
		q.w = (m.m23 - m.m32) * half;

		return q.Normalized();
	}
	else if (m.m22 > m.m33)
	{
		sqrt = sqrtf(1.0f + m.m22 - m.m22 - m.m11);
		half = 0.5f / sqrt;

		q.x = (m.m21 + m.m12) * half;
		q.y = 0.5f * sqrt;
		q.z = (m.m32 + m.m23) * half;
		q.w = (m.m31 - m.m13) * half;

		return q.Normalized();
	}
	else
	{
		sqrt = sqrtf(1.0f + m.m33 - m.m22 - m.m11);
		half = 0.5f / sqrt;

		q.x = (m.m31 + m.m13) * half;
		q.y = (m.m32 + m.m23) * half;
		q.z = 0.5f * sqrt;
		q.w = (m.m12 - m.m21) * half;

		return q.Normalized();
	}
}

Quaternion Quaternion::CreateFromEulerAngles(Vector3 v)
{
	float y = DegreesToRadians(v.y) * 0.5f;
	float x = DegreesToRadians(v.x) * 0.5f;
	float z = DegreesToRadians(v.z) * 0.5f;
	
	float siny = sinf(y);
	float cosy = cosf(y);
	float sinx = sinf(x);
	float cosx = cosf(x);
	float sinz = sinf(z);
	float cosz = cosf(z);

	return Quaternion(
		(cosy * sinx * cosz) + (siny * cosx * sinz),
		(siny * cosx * cosz) - (cosy * sinx * sinz),
		(cosy * cosx * sinz) - (siny * sinx * cosz),
		(cosy * cosx * cosz) + (siny * sinx * sinz)).Normalized();
}

Quaternion Quaternion::Lerp(Quaternion q1, Quaternion q2, float t)
{
	float inv = 1.0f - t;
	Quaternion ret;
	float mult = q1.x*q2.x + q1.y*q2.y + q1.z*q2.z + q1.w*q2.w;
	if (mult > 0.0f)
	{
		ret = Quaternion(inv*q1.x + t*q2.x, inv*q1.y + t*q2.y, inv*q1.z + t*q2.z, inv*q1.w + t*q2.w);
	}
	else
	{
		ret = Quaternion(inv*q1.x - t*q2.x, inv*q1.y - t*q2.y, inv*q1.z - t*q2.z, inv*q1.w - t*q2.w);
	}

	return ret.Normalized();
}

Quaternion Quaternion::Slerp(Quaternion q1, Quaternion q2, float t)
{
	float inv;
	float sign;

	float mult = q1.x*q2.x + q1.y*q2.y + q1.z*q2.z + q1.w*q2.w;
	bool flag = false;
	if (mult < 0.0f)
	{
		flag = true;
	}
	if (mult > 0.99999f)
	{
		inv = 1.0f - t;
		sign = flag ? -t : t;
	}
	else
	{
		float acos = acosf(mult);
		float invsin = 1.0f / sinf(acos);
		inv = sinf((1.0f - t) * acos) * invsin;
		sign = flag ? -sinf(t * acos) * invsin : sinf(t * acos) * invsin;
	}

	return Quaternion(inv*q1.x + sign*q2.x, inv*q1.y + sign*q2.y, inv*q1.z + sign*q2.z, inv*q1.w + sign*q2.w);
}

Quaternion Quaternion::Normalized()
{
	float denom = 1.0f / sqrtf((x*x) + (y*y) + (z*z) + (w*w));
	return Quaternion(x * denom, y * denom, z * denom, w * denom);
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
	float x = (l.w*r.x + l.x*r.w + l.y*r.z - l.z*r.y);
	float y = (l.w*r.y - l.x*r.z + l.y*r.w + l.z*r.x);
	float z = (l.w*r.z + l.x*r.y - l.y*r.x + l.z*r.w);
	float w = (l.w*r.w - l.x*r.x - l.y*r.y - l.z*r.z);
	return Quaternion(x, y, z, w);
}

NS_END