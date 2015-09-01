#ifndef MESH_BUILDER_HPP
#define MESH_BUILDER_HPP

#include "../Config.hpp"
#include "MeshData.hpp"

NS_BEGIN

class Mesh;

enum PrimitiveType
{
	PlaneMesh,
	CubeMesh,
	SphereMesh,
	ConeMesh,
	CylinderMesh
};

/// <summary>
/// Creates primitive meshes from scratch
/// </summary>
class MeshBuilder
{
public:
	/// <summary>
	/// Returns a new mesh object of the given primitive type
	/// </summary>
	static MeshData CreatePrimitive(PrimitiveType pType);
private:
	static MeshData CreatePlane(float width = 10.0f, float depth = 10.0f, UINT n = 2, UINT m = 2);
	static MeshData CreateCube(float width = 1.0f, float depth = 1.0f, float height = 1.0f);
	static MeshData CreateSphere(float radius = 1.0f, UINT numSubdivisons = 2);
	static MeshData CreateOctahedron(float radius = 1.0f, UINT numSubdivision = 0);
	static MeshData CreateCone();
	static MeshData CreateCylinder();

	static void Subdivide(MeshData& data);
	static void SubdivideOct(MeshData& data);	
};

NS_END

#endif