#include"MeshRenderer.hpp"

#include "Vertex.hpp"
#include "Mesh.hpp"
#include "Material.hpp"
#include "GraphicsDevice.hpp"

NS_BEGIN

MeshRenderer::MeshRenderer(Mesh* mesh, Material* mat):
mesh(mesh),
mat(mat),
stride(sizeof(MeshVertex)),
offset(0)
{
	if (!mesh)
	{
#if DEBUG
		Debug::LogError("[MeshRenderer] Initialized without a valid mesh!");
#endif
	}
	else
	{
		std::vector<MeshVertex> verts = mesh->GetVertices();
		std::vector<UINT> inds = mesh->GetIndices();

		if (verts.size() == 0)
		{
#if DEBUG
			Debug::LogError("[MeshRenderer] Initialized with a mesh with 0 vertices!");
#endif
		}

		MeshVertex* vertices = &verts[0];
		UINT* indices = &inds[0];

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));

		D3D11_SUBRESOURCE_DATA srd;
		ZeroMemory(&srd, sizeof(D3D11_SUBRESOURCE_DATA));

		// Vertex Buffer
		bd.Usage = D3D11_USAGE_IMMUTABLE;
		bd.ByteWidth = sizeof(MeshVertex) * mesh->GetNumberOfVertices();
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		srd.pSysMem = vertices;
		GraphicsDevice::GetDevice()->CreateBuffer(&bd, &srd, &vertexBuffer);

		// Index Buffer
		bd.ByteWidth = sizeof(UINT) * mesh->GetNumberOfIndices();
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		srd.pSysMem = indices;
		GraphicsDevice::GetDevice()->CreateBuffer(&bd, &srd, &indexBuffer);
	}
}

MeshRenderer::~MeshRenderer()
{
	DELETECOM(indexBuffer);
	DELETECOM(vertexBuffer);
}

void MeshRenderer::Initialize()
{
	mat->Initialize();
}

void MeshRenderer::BindMesh()
{
	if (vertexBuffer)
	{
		GraphicsDevice::GetDeviceContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	}
	if (indexBuffer)
	{
		GraphicsDevice::GetDeviceContext()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	}
}

void MeshRenderer::BindMaterial()
{
	mat->Bind();
}

void MeshRenderer::SetMaterial(Material* material)
{
	mat = material;
}

void MeshRenderer::Draw()
{
	GraphicsDevice::GetDeviceContext()->DrawIndexed(mesh->GetNumberOfIndices(), 0, 0);
}

NS_END