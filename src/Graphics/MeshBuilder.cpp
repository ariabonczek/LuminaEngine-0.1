#include "MeshBuilder.hpp"

#include "Mesh.hpp"

NS_BEGIN

MeshData MeshBuilder::CreatePrimitive(PrimitiveType pType)
{
	switch (pType)
	{
	case PlaneMesh:
		return CreatePlane();
	case CubeMesh:
		return CreateCube();
	case SphereMesh:
		return CreateSphere();
	case ConeMesh:
		return CreateCone();
	case CylinderMesh:
		return CreateCylinder();
	default:
		// Should never occur
		MeshData d;
#if DEBUG
		Debug::LogError("[MeshBuilder] Somehow this occurred!");
		return d;
#endif
	}
}

MeshData MeshBuilder::CreatePlane(float width, float depth, UINT n, UINT m)
{
	MeshData data;
	n = max(2, n);
	m = max(2, m);

	UINT vertexCount = n * m;
	UINT faceCount = (n - 1)*(m - 1) * 2;

	float halfWidth = width * 0.5f;
	float halfDepth = depth * 0.5f;

	float dx = width / (n - 1);
	float dz = depth / (m - 1);

	float du = 1.0f / (n - 1);
	float dv = 1.0f / (m - 1);

	data.indices.resize(0);
	data.vertices.resize(0);

	for (UINT i = 0; i < m; ++i)
	{
		float z = halfDepth - i * dz;
		for (UINT j = 0; j < n; ++j)
		{
			float x = halfWidth - j * dx;
			MeshVertex cVert;
			cVert.position = Vector3(x, 0.0f, z);
			cVert.normal = Vector3(0.0f, 1.0f, 0.0f);
			cVert.tangent = Vector3(1.0f, 0.0f, 0.0f);
			cVert.texCoord.x = j * du;
			cVert.texCoord.y = i * dv;
			cVert.color = Color(1.0f, 1.0f, 1.0f, 1.0f);
			data.vertices.push_back(cVert);
		}
	}

	UINT k = 0;
	for (UINT i = 0; i < m - 1; ++i)
	{
		for (UINT j = 0; j < n - 1; ++j)
		{
			data.indices.push_back((i + 1) * n + j + 1);
			data.indices.push_back(i * n + j + 1);
			data.indices.push_back((i + 1) * n + j);
			data.indices.push_back((i + 1) * n + j);
			data.indices.push_back(i * n + j + 1);
			data.indices.push_back(i*n + j);
			k += 6;
		}
	}

	return data;
}

MeshData MeshBuilder::CreateCube(float width, float depth, float height)
{
	MeshData data;

	data.vertices.resize(0);
	data.indices.resize(0);

	MeshVertex cVert;
	cVert.color = Color(1.0f, 1.0f, 1.0f, 1.0f);

	///
	// MeshVertex order when facing quad: bottom left, top left, top right, bottom right
	///

	//Front
	cVert.position = Vector3(-width, -height, -depth);
	cVert.normal = Vector3(0.0f, 0.0f, -1.0f);
	cVert.tangent = Vector3(1.0f, 0.0f, 0.0f);
	cVert.texCoord = Vector2(0.0f, 1.0f);
	data.vertices.push_back(cVert);

	cVert.position = Vector3(-width, height, -depth);
	cVert.normal = Vector3(0.0f, 0.0f, -1.0f);
	cVert.tangent = Vector3(1.0f, 0.0f, 0.0f);
	cVert.texCoord = Vector2(0.0f, 0.0f);
	data.vertices.push_back(cVert);

	cVert.position = Vector3(width, height, -depth);
	cVert.normal = Vector3(0.0f, 0.0f, -1.0f);
	cVert.tangent = Vector3(1.0f, 0.0f, 0.0f);
	cVert.texCoord = Vector2(1.0f, 0.0f);
	data.vertices.push_back(cVert);

	cVert.position = Vector3(width, -height, -depth);
	cVert.normal = Vector3(0.0f, 0.0f, -1.0f);
	cVert.tangent = Vector3(1.0f, 0.0f, 0.0f);
	cVert.texCoord = Vector2(1.0f, 1.0f);
	data.vertices.push_back(cVert);

	// Back
	cVert.position = Vector3(-width, -height, depth);
	cVert.normal = Vector3(0.0f, 0.0f, 1.0f);
	cVert.tangent = Vector3(1.0f, 0.0f, 0.0f);
	cVert.texCoord = Vector2(0.0f, 1.0f);
	data.vertices.push_back(cVert);

	cVert.position = Vector3(-width, height, depth);
	cVert.normal = Vector3(0.0f, 0.0f, 1.0f);
	cVert.tangent = Vector3(1.0f, 0.0f, 0.0f);
	cVert.texCoord = Vector2(0.0f, 0.0f);
	data.vertices.push_back(cVert);

	cVert.position = Vector3(width, height, depth);
	cVert.normal = Vector3(0.0f, 0.0f, 1.0f);
	cVert.tangent = Vector3(1.0f, 0.0f, 0.0f);
	cVert.texCoord = Vector2(1.0f, 0.0f);
	data.vertices.push_back(cVert);

	cVert.position = Vector3(width, -height, depth);
	cVert.normal = Vector3(0.0f, 0.0f, 1.0f);
	cVert.tangent = Vector3(1.0f, 0.0f, 0.0f);
	cVert.texCoord = Vector2(1.0f, 1.0f);
	data.vertices.push_back(cVert);

	// Left
	cVert.position = Vector3(-width, -height, depth);
	cVert.normal = Vector3(-1.0f, 0.0f, 0.0f);
	cVert.tangent = Vector3(0.0f, 0.0f, -1.0f);
	cVert.texCoord = Vector2(0.0f, 1.0f);
	data.vertices.push_back(cVert);

	cVert.position = Vector3(-width, height, depth);
	cVert.normal = Vector3(-1.0f, 0.0f, 0.0f);
	cVert.tangent = Vector3(0.0f, 0.0f, -1.0f);
	cVert.texCoord = Vector2(0.0f, 0.0f);
	data.vertices.push_back(cVert);

	cVert.position = Vector3(-width, height, -depth);
	cVert.normal = Vector3(-1.0f, 0.0f, 0.0f);
	cVert.tangent = Vector3(0.0f, 0.0f, -1.0f);
	cVert.texCoord = Vector2(1.0f, 0.0f);
	data.vertices.push_back(cVert);

	cVert.position = Vector3(-width, -height, -depth);
	cVert.normal = Vector3(-1.0f, 0.0f, 0.0f);
	cVert.tangent = Vector3(0.0f, 0.0f, -1.0f);
	cVert.texCoord = Vector2(1.0f, 1.0f);
	data.vertices.push_back(cVert);

	// Right
	cVert.position = Vector3(width, -height, -depth);
	cVert.normal = Vector3(1.0f, 0.0f, 0.0f);
	cVert.tangent = Vector3(0.0f, 0.0f, -1.0f);
	cVert.texCoord = Vector2(0.0f, 1.0f);
	data.vertices.push_back(cVert);

	cVert.position = Vector3(width, height, -depth);
	cVert.normal = Vector3(1.0f, 0.0f, 0.0f);
	cVert.tangent = Vector3(0.0f, 0.0f, -1.0f);
	cVert.texCoord = Vector2(0.0f, 0.0f);
	data.vertices.push_back(cVert);

	cVert.position = Vector3(width, height, depth);
	cVert.normal = Vector3(1.0f, 0.0f, 0.0f);
	cVert.tangent = Vector3(0.0f, 0.0f, -1.0f);
	cVert.texCoord = Vector2(1.0f, 0.0f);
	data.vertices.push_back(cVert);

	cVert.position = Vector3(width, -height, depth);
	cVert.normal = Vector3(1.0f, 0.0f, 0.0f);
	cVert.tangent = Vector3(0.0f, 0.0f, -1.0f);
	cVert.texCoord = Vector2(1.0f, 1.0f);
	data.vertices.push_back(cVert);

	// Top
	cVert.position = Vector3(-width, height, -depth);
	cVert.normal = Vector3(0.0f, 1.0f, 0.0f);
	cVert.tangent = Vector3(1.0f, 0.0f, 0.0f);
	cVert.texCoord = Vector2(0.0f, 1.0f);
	data.vertices.push_back(cVert);

	cVert.position = Vector3(-width, height, depth);
	cVert.normal = Vector3(0.0f, 1.0f, 0.0f);
	cVert.tangent = Vector3(1.0f, 0.0f, 0.0f);
	cVert.texCoord = Vector2(0.0f, 0.0f);
	data.vertices.push_back(cVert);

	cVert.position = Vector3(width, height, depth);
	cVert.normal = Vector3(0.0f, 1.0f, 0.0f);
	cVert.tangent = Vector3(1.0f, 0.0f, 0.0f);
	cVert.texCoord = Vector2(1.0f, 0.0f);
	data.vertices.push_back(cVert);

	cVert.position = Vector3(width, height, -depth);
	cVert.normal = Vector3(0.0f, 1.0f, 0.0f);
	cVert.tangent = Vector3(1.0f, 0.0f, 0.0f);
	cVert.texCoord = Vector2(1.0f, 1.0f);
	data.vertices.push_back(cVert);

	// Bottom
	cVert.position = Vector3(-width, -height, -depth);
	cVert.normal = Vector3(0.0f, -1.0f, 0.0f);
	cVert.tangent = Vector3(1.0f, 0.0f, 0.0f);
	cVert.texCoord = Vector2(0.0f, 1.0f);
	data.vertices.push_back(cVert);

	cVert.position = Vector3(-width, -height, depth);
	cVert.normal = Vector3(0.0f, -1.0f, 0.0f);
	cVert.tangent = Vector3(1.0f, 0.0f, 0.0f);
	cVert.texCoord = Vector2(0.0f, 0.0f);
	data.vertices.push_back(cVert);

	cVert.position = Vector3(width, -height, depth);
	cVert.normal = Vector3(0.0f, -1.0f, 0.0f);
	cVert.tangent = Vector3(1.0f, 0.0f, 0.0f);
	cVert.texCoord = Vector2(1.0f, 0.0f);
	data.vertices.push_back(cVert);

	cVert.position = Vector3(width, -height, -depth);
	cVert.normal = Vector3(0.0f, -1.0f, 0.0f);
	cVert.tangent = Vector3(1.0f, 0.0f, 0.0f);
	cVert.texCoord = Vector2(1.0f, 1.0f);
	data.vertices.push_back(cVert);

	// INDICES
	data.indices.push_back(0);
	data.indices.push_back(1);
	data.indices.push_back(3);
	data.indices.push_back(3);
	data.indices.push_back(1);
	data.indices.push_back(2);

	data.indices.push_back(4);
	data.indices.push_back(6);
	data.indices.push_back(5);
	data.indices.push_back(6);
	data.indices.push_back(4);
	data.indices.push_back(7);

	data.indices.push_back(8);
	data.indices.push_back(9);
	data.indices.push_back(10);
	data.indices.push_back(10);
	data.indices.push_back(11);
	data.indices.push_back(8);

	data.indices.push_back(12);
	data.indices.push_back(13);
	data.indices.push_back(14);
	data.indices.push_back(14);
	data.indices.push_back(15);
	data.indices.push_back(12);

	data.indices.push_back(16);
	data.indices.push_back(17);
	data.indices.push_back(18);
	data.indices.push_back(18);
	data.indices.push_back(19);
	data.indices.push_back(16);

	data.indices.push_back(20);
	data.indices.push_back(22);
	data.indices.push_back(21);
	data.indices.push_back(20);
	data.indices.push_back(23);
	data.indices.push_back(22);

	return data;
}

MeshData MeshBuilder::CreateSphere(float radius, UINT numSubdivisions)
{
	MeshData data;

	// Hard cap on number of subdivisions
	numSubdivisions = min(numSubdivisions, 5u);

	const float X = 0.525731f;
	const float Z = 0.850651f;

	Vector3 pos[12] =
	{
		Vector3(-X, 0.0f, Z), Vector3(X, 0.0f, Z),
		Vector3(-X, 0.0f, -Z), Vector3(X, 0.0f, -Z),
		Vector3(0.0f, Z, X), Vector3(0.0f, Z, -X),
		Vector3(0.0f, -Z, X), Vector3(0.0f, -Z, -X),
		Vector3(Z, X, 0.0f), Vector3(-Z, X, 0.0f),
		Vector3(Z, -X, 0.0f), Vector3(-Z, -X, 0.0f)
	};

	UINT ind[60] =
	{
		1, 4, 0, 4, 9, 0, 4, 5, 9, 8, 5, 4, 1, 8, 4,
		1, 10, 8, 10, 3, 8, 8, 3, 5, 3, 2, 5, 3, 7, 2,
		3, 10, 7, 10, 6, 7, 6, 11, 7, 6, 0, 11, 6, 1, 0,
		10, 1, 6, 11, 0, 9, 2, 11, 9, 5, 2, 9, 11, 2, 7
	};

	data.vertices.resize(12);
	data.indices.resize(60);

	for (byte i = 0; i < 12; i++)
	{
		data.vertices[i].position = pos[i];
	}

	for (byte i = 0; i < 60; i++)
	{
		data.indices[i] = ind[i];
	}

	for (byte i = 0; i < numSubdivisions; i++)
	{
		Subdivide(data);
	}

	for (UINT i = 0; i < data.vertices.size(); ++i)
	{
		data.vertices[i].position.Normalize();
		data.vertices[i].normal = data.vertices[i].position;

		Vector3 p = Vector3::Multiply(data.vertices[i].position, radius);
		data.vertices[i].position = p;

		float theta = atan2(data.vertices[i].position.x, data.vertices[i].position.z);

		float phi = acosf(data.vertices[i].position.y / radius);

		data.vertices[i].texCoord.x = theta / TWOPI;
		data.vertices[i].texCoord.y = phi / PI;

		data.vertices[i].tangent.x = -radius*sinf(phi)*sinf(theta);
		data.vertices[i].tangent.y = 0.0f;
		data.vertices[i].tangent.z = +radius*sinf(phi)*cosf(theta);

		data.vertices[i].tangent.Normalize();
	}
	return data;
}

MeshData MeshBuilder::CreateCone()
{
	MeshData data;
#ifdef DEBUG
	Debug::Log("[MeshBuilder] CreateCone not yet implemented!");
#endif
	return data;
}

MeshData MeshBuilder::CreateCylinder()
{
	MeshData data;
#ifdef DEBUG
	Debug::Log("[MeshBuilder] CreateCylinder not yet implemented!");
#endif
	return data;
}

void MeshBuilder::Subdivide(MeshData& data)
{
	MeshData copy = data;

	// TODO: May be a better way to optimize this
	data.vertices.resize(0);
	data.indices.resize(0);

	UINT numTris = copy.indices.size() / 3;
	for (UINT i = 0; i < numTris; ++i)
	{
		MeshVertex v0 = copy.vertices[copy.indices[i * 3 + 0]];
		MeshVertex v1 = copy.vertices[copy.indices[i * 3 + 1]];
		MeshVertex v2 = copy.vertices[copy.indices[i * 3 + 2]];

		MeshVertex m0, m1, m2;

		m0.position = Vector3(
			0.5f*(v0.position.x + v1.position.x),
			0.5f*(v0.position.y + v1.position.y),
			0.5f*(v0.position.z + v1.position.z));

		m1.position = Vector3(
			0.5f*(v1.position.x + v2.position.x),
			0.5f*(v1.position.y + v2.position.y),
			0.5f*(v1.position.z + v2.position.z));

		m2.position = Vector3(
			0.5f*(v0.position.x + v2.position.x),
			0.5f*(v0.position.y + v2.position.y),
			0.5f*(v0.position.z + v2.position.z));

		data.vertices.push_back(v0); // 0
		data.vertices.push_back(v1); // 1
		data.vertices.push_back(v2); // 2
		data.vertices.push_back(m0); // 3
		data.vertices.push_back(m1); // 4
		data.vertices.push_back(m2); // 5

		data.indices.push_back(i * 6 + 0);
		data.indices.push_back(i * 6 + 3);
		data.indices.push_back(i * 6 + 5);

		data.indices.push_back(i * 6 + 3);
		data.indices.push_back(i * 6 + 4);
		data.indices.push_back(i * 6 + 5);

		data.indices.push_back(i * 6 + 5);
		data.indices.push_back(i * 6 + 4);
		data.indices.push_back(i * 6 + 2);
		
		data.indices.push_back(i * 6 + 3);
		data.indices.push_back(i * 6 + 1);
		data.indices.push_back(i * 6 + 4);
	}
}

NS_END