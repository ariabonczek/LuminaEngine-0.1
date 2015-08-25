#ifndef MESHDATA_HPP
#define MESHDATA_HPP

#include "../Config.hpp"

#include "Vertex.hpp"

NS_BEGIN

/// <summary>
/// Stores raw mesh vertex and index data
/// </summary>
struct MeshData
{
	std::vector<MeshVertex> vertices;
	std::vector<UINT> indices;

	/// <summary>
	/// Combine two MeshData objects to create one
	/// </summary>
	void Append(MeshData data);
};

NS_END

#endif