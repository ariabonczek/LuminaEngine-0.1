#ifndef MESH_RENDERER_HPP
#define MESH_RENDERER_HPP

#include "../Config.hpp"

#include "../Objects/Component.hpp"

NS_BEGIN

class Mesh;

class MeshRenderer : public Component
{
public:
	MeshRenderer(Mesh* mesh);
	~MeshRenderer();

	void Initialize();

	void Bind();
	
	// TODO: Remove this when batch rendering setup
	void Draw();
private:
	Mesh* mesh;

	ID3D11Buffer* indexBuffer;
	ID3D11Buffer* vertexBuffer;

	UINT stride;
	UINT offset;
};

NS_END


#endif