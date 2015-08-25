#ifndef MESH_HPP
#define MESH_HPP

#include "../Config.hpp"

#include "../Utility/Resource.hpp"

#include "MeshData.hpp"

NS_BEGIN

class GraphicsDevice;

class Mesh : public Resource
{
public:
	Mesh(MeshData data);
	~Mesh();

	/// <summary>
	/// Returns the number of vertices in the mesh
	/// </summary>
	uint GetNumberOfVertices()const;

	/// <summary>
	/// Returns the number of indices in the mesh
	/// </summary>
	uint GetNumberOfIndices()const;

	/// <summary>
	/// Returns a vector of Mesh vertices
	/// </summary>
	std::vector<MeshVertex> GetVertices()const;

	/// <summary>
	/// Returns a vector of Mesh indicies
	/// </summary>
	std::vector<UINT> GetIndices()const;
private:
	MeshData data;
};

NS_END

#endif