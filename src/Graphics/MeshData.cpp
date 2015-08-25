#include "MeshData.hpp"

NS_BEGIN

// TODO: Optimize vector resizing
// (NOTE: Do this in other places as well)
void MeshData::Append(MeshData data)
{
	for (std::vector<MeshVertex>::iterator i = data.vertices.begin(); i != data.vertices.end(); ++i)
	{
		vertices.push_back(*i);
	}

	for (std::vector<UINT>::iterator i = data.indices.begin(); i != data.indices.end(); ++i)
	{
		indices.push_back(*i);
	}
}

NS_END