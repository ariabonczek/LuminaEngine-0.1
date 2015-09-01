#ifndef MESH_RENDERER_HPP
#define MESH_RENDERER_HPP

#include "../Config.hpp"

#include "../Objects/Component.hpp"
#include "Material.hpp"

NS_BEGIN

class Mesh;
class Material;

class MeshRenderer : public Component
{
public:
	MeshRenderer(Mesh* mesh, Material* mat = Material::Default);
	~MeshRenderer();

	void Initialize();

	void BindMesh();
	void BindMaterial();

	void SetMaterial(Material* material);
	
	// TODO: Remove this when batch rendering setup
	// Keep it there for batchless rendering
	void Draw();
private:
	Mesh* mesh;
	Material* mat;

	ID3D11Buffer* indexBuffer;
	ID3D11Buffer* vertexBuffer;

	UINT stride;
	UINT offset;
};

NS_END


#endif