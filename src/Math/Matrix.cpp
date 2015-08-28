#include "Matrix.hpp"
#include "Vector.hpp"
#include "Quaternion.hpp"

NS_BEGIN

Matrix Matrix::Identity(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);

Matrix::Matrix() :
m11(0), m12(0), m13(0), m14(0),
m21(0), m22(0), m23(0), m24(0),
m31(0), m32(0), m33(0), m34(0),
m41(0), m42(0), m43(0), m44(0)
{}

Matrix::Matrix(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44) :
m11(m11), m12(m12), m13(m13), m14(m14),
m21(m21), m22(m22), m23(m23), m24(m24),
m31(m31), m32(m32), m33(m33), m34(m34),
m41(m41), m42(m42), m43(m43), m44(m44)
{}

float Matrix::Determinant()
{
	return m11 * DeterminantHelper(m22, m23, m24, m32, m33, m34, m42, m43, m44) -
		m12 * DeterminantHelper(m21, m23, m24, m31, m33, m34, m41, m43, m44) +
		m13 * DeterminantHelper(m21, m22, m24, m31, m32, m34, m41, m42, m44) -
		m14 * DeterminantHelper(m21, m22, m23, m31, m32, m33, m41, m42, m43);
}
 
Matrix  Matrix::Transpose()
{
	return Matrix(m11, m21, m31, m41, m12, m22, m32, m42, m13, m23, m33, m43, m14, m24, m34, m44);
}

Vector3 Matrix::Right()
{
	return Vector3(m11, m12, m13);
}

Vector3 Matrix::Up()
{
	return Vector3(m21, m22, m23);
}

Vector3 Matrix::Forward()
{
	return Vector3(m31, m32, m33);
}

Matrix Matrix::operator+(const Matrix& m)
{
	return Matrix(m11 + m.m11, m12 + m.m12, m13 + m.m13, m14 + m.m14,
		m21 + m.m21, m22 + m.m22, m23 + m.m23, m24 + m.m24,
		m31 + m.m31, m32 + m.m32, m33 + m.m33, m34 + m.m34,
		m41 + m.m41, m42 + m.m42, m43 + m.m43, m44 + m.m44);
}

Matrix Matrix::operator-(const Matrix& m)
{
	return Matrix(m11 - m.m11, m12 - m.m12, m13 - m.m13, m14 - m.m14,
		21 - m.m21, m22 - m.m22, m23 - m.m23, m24 - m.m24,
		m31 - m.m31, m32 - m.m32, m33 - m.m33, m34 - m.m34,
		m41 - m.m41, m42 - m.m42, m43 - m.m43, m44 - m.m44);
}

Matrix operator*(const Matrix& l, const Matrix& r)
{
	return Matrix(
		((l.m11 * r.m11) + (l.m12 * r.m21) + (l.m13 * r.m31) + (l.m14 * r.m41)),
		((l.m11 * r.m12) + (l.m12 * r.m22) + (l.m13 * r.m32) + (l.m14 * r.m42)),
		((l.m11 * r.m13) + (l.m12 * r.m23) + (l.m13 * r.m33) + (l.m14 * r.m43)),
		((l.m11 * r.m14) + (l.m12 * r.m24) + (l.m13 * r.m34) + (l.m14 * r.m44)),

		((l.m21 * r.m11) + (l.m22 * r.m21) + (l.m23 * r.m31) + (l.m24 * r.m41)),
		((l.m21 * r.m12) + (l.m22 * r.m22) + (l.m23 * r.m32) + (l.m24 * r.m42)),
		((l.m21 * r.m13) + (l.m22 * r.m23) + (l.m23 * r.m33) + (l.m24 * r.m43)),
		((l.m21 * r.m14) + (l.m22 * r.m24) + (l.m23 * r.m34) + (l.m24 * r.m44)),

		((l.m31 * r.m11) + (l.m32 * r.m21) + (l.m33 * r.m31) + (l.m34 * r.m41)),
		((l.m31 * r.m12) + (l.m32 * r.m22) + (l.m33 * r.m32) + (l.m34 * r.m42)),
		((l.m31 * r.m13) + (l.m32 * r.m23) + (l.m33 * r.m33) + (l.m34 * r.m43)),
		((l.m31 * r.m14) + (l.m32 * r.m24) + (l.m33 * r.m34) + (l.m34 * r.m44)),

		((l.m41 * r.m11) + (l.m42 * r.m21) + (l.m43 * r.m31) + (l.m44 * r.m41)),
		((l.m41 * r.m12) + (l.m42 * r.m22) + (l.m43 * r.m32) + (l.m44 * r.m42)),
		((l.m41 * r.m13) + (l.m42 * r.m23) + (l.m43 * r.m33) + (l.m44 * r.m43)),
		((l.m41 * r.m14) + (l.m42 * r.m24) + (l.m43 * r.m34) + (l.m44 * r.m44))
		);
}

Matrix Matrix::operator/(const Matrix& m)
{
	return Matrix(
		m11 / m.m11, m12 / m.m12, m13 / m.m13, m14 / m.m14,
		m21 / m.m21, m22 / m.m22, m23 / m.m23, m24 / m.m24,
		m31 / m.m31, m32 / m.m32, m33 / m.m33, m34 / m.m34,
		m41 / m.m41, m42 / m.m42, m43 / m.m43, m44 / m.m44
		);
}

Matrix Matrix::operator/(const float& f)
{
	return Matrix(
		m11 / f, m12 / f, m13 / f, m14 / f,
		m21 / f, m22 / f, m23 / f, m24 / f,
		m31 / f, m32 / f, m33 / f, m34 / f,
		m41 / f, m42 / f, m43 / f, m44 / f
		);
}

bool Matrix::operator==(const Matrix& m)
{
	return
		(m11 == m.m11) && (m12 == m.m12) && (m13 == m.m13) && (m14 == m.m14) &&
		(m21 == m.m21) && (m22 == m.m22) && (m23 == m.m23) && (m24 == m.m24) &&
		(m31 == m.m31) && (m32 == m.m32) && (m33 == m.m33) && (m34 == m.m34) &&
		(m41 == m.m41) && (m42 == m.m42) && (m43 == m.m43) && (m44 == m.m44);
}

Matrix operator*(const Matrix& m, float s)
{
	return Matrix(
		m.m11 * s, m.m12 * s, m.m13 *s, m.m14 * s,
		m.m21 * s, m.m22 * s, m.m23 *s, m.m24 * s,
		m.m31 * s, m.m32 * s, m.m33 *s, m.m34 *s,
		m.m41 * s, m.m42 * s, m.m43 *s, m.m44 * s
		);
}

Matrix operator*(float s, Matrix& m)
{
	return Matrix(
		m.m11 * s, m.m12 * s, m.m13 * s, m.m14 * s,
		m.m21 * s, m.m22 * s, m.m23 * s, m.m24 * s,
		m.m31 * s, m.m32 * s, m.m33 * s, m.m34 * s,
		m.m41 * s, m.m42 * s, m.m43 * s, m.m44 * s
		);
}

float Matrix::operator[](int index)
{
	switch (index)
	{
	case 0:
		return m11;
	case 1:
		return m12;
	case 2:
		return m13;
	case 3:
		return m14;
	case 4:
		return m21;
	case 5:
		return m22;
	case 6:
		return m23;
	case 7:
		return m24;
	case 8:
		return m31;
	case 9:
		return m32;
	case 10:
		return m33;
	case 11:
		return m34;
	case 12:
		return m41;
	case 13:
		return m42;
	case 14:
		return m43;
	case 15:
		return m44;
	default:
		throw "[Matrix] IndexOutOfRange Exception";
	}
}


Matrix Matrix::Add(Matrix& m1, Matrix& m2)
{
	return m1 + m2;
}

Matrix Matrix::Subtract(Matrix& m1, Matrix& m2)
{
	return m1 - m2;
}

Matrix Matrix::CreateFromQuaternion(Quaternion q)
{
	float x2 = q.x*q.x;
	float y2 = q.y*q.y;
	float z2 = q.z*q.z;
	float xy = q.x*q.y;
	float zw = q.z*q.w;
	float xz = q.z*q.x;
	float yw = q.y*q.w;
	float yz = q.y*q.z;
	float xw = q.x*q.w;

	return Matrix(
		1.0f - (2.0f * (y2 + z2)), 2.0f * (xy + zw),          2.0f * (xz - yw), 0.0f,
		2.0f * (xy - zw),		   1.0f - (2.0f * (z2 + x2)), 2.0f * (yz + xw), 0.0f,
		2.0f * (xz + yw),		   2.0f * (yz - xw),          1.0f - (2.0f * (y2 + x2)), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix Matrix::CreateLookAt(Vector3 position, Vector3 target, Vector3 up)
{
	Vector3 v = Vector3::Normalize(position - target);
	Vector3 v2 = Vector3::Normalize(Vector3::Cross(up, v));
	Vector3 v3 = Vector3::Cross(v, v2);

	return Matrix(v2.x, v3.x, v.x, 0.0f,
		v2.y, v3.y, v.y, 0.0f,
		v2.z, v3.z, v.z, 0.0f,
		-Vector3::Dot(v2, position), -Vector3::Dot(v3, position), -Vector3::Dot(v, position), 1.0f);
}

Matrix Matrix::CreateOrthographic(float width, float height, float zNear, float zFar)
{
	if (zNear >= zFar)
		throw "[Matrix] Invalid zNear and zFar values.";

	return Matrix(2.0f / width, 0.0f, 0.0f, 0.0f,
		0.0f, 2.0f / height, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f / (zNear - zFar), 0.0f,
		0.0f, 0.0f, zNear / (zNear - zFar), 1.0f);
}

Matrix Matrix::CreatePerspective(float width, float height, float zNear, float zFar)
{
	if (zNear >= zFar)
		throw "[Matrix] Invalid zNear and zFar values.";

	return Matrix((2.0f * zNear) / width, 0.0f, 0.0f, 0.0f,
		0.0f, (2.0f * zNear) / height, 0.0f, 0.0f, 
		0.0f, 0.0f, zFar / (zFar - zNear), 1.0f, 
		0.0f, 0.0f, -(zNear * zFar) / (zFar - zNear), 0.0f);
}

Matrix Matrix::CreatePerspectiveFov(float fov, float aspect, float zNear, float zFar)
{
	if ((fov <= 0.0f) || (fov >= PI))
		throw "[Matrix] fov <= 0 or >= PI";
	if (zNear >= zFar)
		throw "[Matrix] Invalid zNear and zFar values.";

	float n = 1.0f / ((float)tanf(fov * 0.5f));
	float n2 = n / aspect;
	return Matrix(n2, 0.0f, 0.0f, 0.0f,
		0.0f, n, 0.0f, 0.0f,
		0.0f, 0.0f, zFar / (zFar - zNear), 1.0f,
		0.0f, 0.0f, -(zNear * zFar) / (zFar - zNear), 0.0f);
}

Matrix Matrix::CreateRotationByAxisAngle(Vector3 axis, float angle)
{
	float x = axis.x;
	float y = axis.y;
	float z = axis.z;
	
	float sin = sinf(DegreesToRadians(-angle));
	float cos = cosf(DegreesToRadians(-angle));

	float x2 = x*x;
	float y2 = y*y;
	float z2 = z*z;

	float xy = x*y;
	float xz = x*z;
	float yz = y*z;

	return Matrix(x2 + (cos * (1.0f - x2)), (xy - (cos * xy)) + (sin * z), (xz - (cos * xz)) - (sin * y), 0.0f,
		(xy - (cos * xy)) - (sin * z), y2 + (cos * (1.0f - y2)), (yz - (cos * yz)) + sin * x, 0.0f,
		(xz - (cos * xz)) + sin * y, (yz - (cos * yz)) - sin * x, z2 + (cos * (1.0f - z2)), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);	
}

Matrix Matrix::CreateRotationX(float angle)
{
	float sin = sinf(DegreesToRadians(-angle));
	float cos = cosf(DegreesToRadians(-angle));

	return Matrix(1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, cos, -sin, 0.0f,
		0.0f, sin, cos, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix Matrix::CreateRotationY(float angle)
{
	float sin = sinf(DegreesToRadians(-angle));
	float cos = cosf(DegreesToRadians(-angle));

	return Matrix(cos, 0.0f, sin, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		-sin, 0.0f, cos, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);

}

Matrix Matrix::CreateRotationZ(float angle)
{
	float sin = sinf(DegreesToRadians(-angle));
	float cos = cosf(DegreesToRadians(-angle));

	return Matrix(cos, -sin, 0.0f, 0.0f,
		sin, cos, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}

// TODO: Optimize this (super easy)
Matrix Matrix::CreateRotation(Vector3 rotation)
{
	Matrix x = CreateRotationX(rotation.x);
	Matrix y = CreateRotationY(rotation.y);
	Matrix z = CreateRotationZ(rotation.z);

	return z * x * y;
}

Matrix Matrix::CreateScale(float scale)
{
	return Matrix(scale, 0.0f, 0.0f, 0.0f,
		0.0f, scale, 0.0f, 0.0f,
		0.0f, 0.0f, scale, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix Matrix::CreateScale(float x, float y, float z)
{
	return Matrix(x, 0.0f, 0.0f, 0.0f,
		0.0f, y, 0.0f, 0.0f,
		0.0f, 0.0f, z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix Matrix::CreateScale(Vector3 scale)
{
	return Matrix(scale.x, 0.0f, 0.0f, 0.0f,
		0.0f, scale.y, 0.0f, 0.0f,
		0.0f, 0.0f, scale.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix Matrix::CreateTranslation(float x, float y, float z)
{
	return Matrix(1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		x, y, z, 1.0f);
}

Matrix Matrix::CreateTranslation(Vector3 translation)
{
	return Matrix(1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		translation.x, translation.y, translation.z, 1.0f);
}

Matrix Matrix::CreateWorld(Vector3 position, Vector3 forward, Vector3 up)
{
	Vector3 x, y, z;
	z = Vector3::Normalize(forward);
	x = Vector3::Normalize(Vector3::Cross(z, up));
	y = Vector3::Normalize(Vector3::Cross(x, z));
	
	return Matrix(x.x, x.y, x.z, 0.0f,
		y.x, y.y, y.z, 0.0f, 
		z.x, z.y, z.z, 0.0f,
		position.x, position.y, position.z, 1.0f);

}

Matrix Matrix::Inverse(Matrix m)
{
	// Source: https://github.com/mono/MonoGame/blob/develop/MonoGame.Framework/Matrix.cs
	float num1 =m.m11;
	float num2 =m.m12;
	float num3 =m.m13;
	float num4 =m.m14;
	float num5 =m.m21;
	float num6 =m.m22;
	float num7 =m.m23;
	float num8 =m.m24;
	float num9 =m.m31;
	float num10 = m.m32;
	float num11 = m.m33;
	float num12 = m.m34;
	float num13 = m.m41;
	float num14 = m.m42;
	float num15 = m.m43;
	float num16 = m.m44;
	float num17 = (float)((double)num11 * (double)num16 - (double)num12 * (double)num15);
	float num18 = (float)((double)num10 * (double)num16 - (double)num12 * (double)num14);
	float num19 = (float)((double)num10 * (double)num15 - (double)num11 * (double)num14);
	float num20 = (float)((double)num9 * (double)num16 - (double)num12 * (double)num13);
	float num21 = (float)((double)num9 * (double)num15 - (double)num11 * (double)num13);
	float num22 = (float)((double)num9 * (double)num14 - (double)num10 * (double)num13);
	float num23 = (float)((double)num6 * (double)num17 - (double)num7 * (double)num18 + (double)num8 * (double)num19);
	float num24 = (float)-((double)num5 * (double)num17 - (double)num7 * (double)num20 + (double)num8 * (double)num21);
	float num25 = (float)((double)num5 * (double)num18 - (double)num6 * (double)num20 + (double)num8 * (double)num22);
	float num26 = (float)-((double)num5 * (double)num19 - (double)num6 * (double)num21 + (double)num7 * (double)num22);
	float num27 = (float)(1.0 / ((double)num1 * (double)num23 + (double)num2 * (double)num24 + (double)num3 * (double)num25 + (double)num4 * (double)num26));
	float num28 = (float)((double)num7 * (double)num16 - (double)num8 * (double)num15);
	float num29 = (float)((double)num6 * (double)num16 - (double)num8 * (double)num14);
	float num30 = (float)((double)num6 * (double)num15 - (double)num7 * (double)num14);
	float num31 = (float)((double)num5 * (double)num16 - (double)num8 * (double)num13);
	float num32 = (float)((double)num5 * (double)num15 - (double)num7 * (double)num13);
	float num33 = (float)((double)num5 * (double)num14 - (double)num6 * (double)num13);
	float num34 = (float)((double)num7 * (double)num12 - (double)num8 * (double)num11);
	float num35 = (float)((double)num6 * (double)num12 - (double)num8 * (double)num10);
	float num36 = (float)((double)num6 * (double)num11 - (double)num7 * (double)num10);
	float num37 = (float)((double)num5 * (double)num12 - (double)num8 * (double)num9);
	float num38 = (float)((double)num5 * (double)num11 - (double)num7 * (double)num9);
	float num39 = (float)((double)num5 * (double)num10 - (double)num6 * (double)num9);

	return Matrix(num23 * num27,
		(float)-((double)num2 * (double)num17 - (double)num3 * (double)num18 + (double)num4 * (double)num19) * num27,
		(float)((double)num2 * (double)num28 - (double)num3 * (double)num29 + (double)num4 * (double)num30) * num27,
		(float)-((double)num2 * (double)num34 - (double)num3 * (double)num35 + (double)num4 * (double)num36) * num27,
		num24 * num27,
		(float)((double)num1 * (double)num17 - (double)num3 * (double)num20 + (double)num4 * (double)num21) * num27,
		(float)-((double)num1 * (double)num28 - (double)num3 * (double)num31 + (double)num4 * (double)num32) * num27,
		(float)((double)num1 * (double)num34 - (double)num3 * (double)num37 + (double)num4 * (double)num38) * num27,
		num25 * num27,
		(float)-((double)num1 * (double)num18 - (double)num2 * (double)num20 + (double)num4 * (double)num22) * num27,
		(float)((double)num1 * (double)num29 - (double)num2 * (double)num31 + (double)num4 * (double)num33) * num27,
		(float)-((double)num1 * (double)num35 - (double)num2 * (double)num37 + (double)num4 * (double)num39) * num27,
		num26 * num27,
		(float)((double)num1 * (double)num19 - (double)num2 * (double)num21 + (double)num3 * (double)num22) * num27,
		(float)-((double)num1 * (double)num30 - (double)num2 * (double)num32 + (double)num3 * (double)num33) * num27,
		(float)((double)num1 * (double)num36 - (double)num2 * (double)num38 + (double)num3 * (double)num39) * num27);
	
}

Matrix Matrix::Transpose(Matrix m)
{
	return Matrix(m.m11, m.m21, m.m31, m.m41, m.m12, m.m22, m.m32, m.m42, m.m13, m.m23, m.m33, m.m43, m.m14, m.m24, m.m34, m.m44);
}

Vector3 Matrix::RotationToEuler(Matrix m)
{
	// Source: https://d3cw3dd2w32x2b.cloudfront.net/wp-content/uploads/2012/07/euler-angles1.pdf
	float theta1 = atan2f(m.m23, m.m33);
	float c2 = sqrt(m.m11*m.m11 + m.m12*m.m12);
	float theta2 = atan2f(-m.m13, c2);
	float c1 = cosf(theta1);
	float s1 = sinf(theta1);
	float theta3 = atan2f(s1*m.m31 - c1*m.m21, c1*m.m22 -s1*m.m32);
	return Vector3(theta1, theta2, theta3);
}

float Matrix::DeterminantHelper(float m11, float m12, float m13, float m21, float m22, float m23, float m31, float m32, float m33)
{
	float d11 = m22*m33 - m23*m32;
	float d12 = m21*m33 - m23*m31;
	float d13 = m21*m32 - m22*m31;

	return m11*d11 - m12*d12 + m13*d13;
}

NS_END