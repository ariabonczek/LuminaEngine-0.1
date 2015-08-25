#include "Mesh.hpp"

#include "GraphicsDevice.hpp"

NS_BEGIN

Mesh::Mesh(MeshData data):
data(data)
{
	Resource::Resource();
}

Mesh::~Mesh()
{

}

uint Mesh::GetNumberOfVertices()const
{
	return data.vertices.size();
}

uint Mesh::GetNumberOfIndices()const
{
	return data.indices.size();
}

std::vector<MeshVertex> Mesh::GetVertices()const
{
	return data.vertices;
}

std::vector<UINT> Mesh::GetIndices()const
{
	return data.indices;
}

NS_END