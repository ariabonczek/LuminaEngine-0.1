#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "../Config.hpp"
#include "../Math/Math.hpp"
#include "Color.hpp"

NS_BEGIN

enum VertexType
{
	BaseVert,
	ColoredVert,
	MeshVert,
	ParticleVert
};

struct Vertex 
{
	Vector3 position;
	Vector2 texCoord;
};

struct ColoredVertex
{
	Vector3 position;
	Vector2 texCoord;
	Color color;
};

struct MeshVertex
{
	Vector3 position;
	Color color;
	Vector2 texCoord;
	Vector3 normal;
	Vector3 tangent;
};

struct Particle
{

};

NS_END

#endif