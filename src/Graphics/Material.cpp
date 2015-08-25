#include "Material.hpp"

#include "GraphicsDevice.hpp"
#include "../Math/Math.hpp"
#include "Color.hpp"
#include "Texture2D.hpp"

NS_BEGIN

// TODO: Clean up this and shader implementation

Material* Material::Default;

Material::Material(Shader* shader):
shader(shader)
{}

Material::Material(Material* material)
{
	shader = material->shader;
}

Material::~Material()
{
	// TODO: Double check for shader memory leaks since its not being handled by the ResourceManager
	DELETECOM(propertyBuffer);
}

void Material::Initialize()
{
	shader->Initialize();

	uint bytesleft = (sizeof(float) * shader->data.size()) % 16;
	if (bytesleft != 0)
	{
#if DEBUG
		if (bytesleft % 4 != 0)
		{
			Debug::LogError("[Material] Error: expected 4 byte aligned and got: " + std::to_string(bytesleft % 4));
		}
#endif
		uint count = bytesleft / 4;
		for (uint i = 0; i < count; i++)
		{
			shader->data.push_back(0.0f);
		}
	}

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.ByteWidth = sizeof(float) * shader->data.size();

	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;

	HRESULT hr = GraphicsDevice::GetDevice()->CreateBuffer(&bd, 0, &propertyBuffer);
}

void Material::ShutdownStatic()
{
	delete Default;
}

template<typename T>
void Material::SetPropertyValue(std::string name, T val)
{
	// TODO: Check if the value type and T are the same
	if (shader->propertyMap.find(name) != shader->propertyMap.end())
	{
		size_t size = sizeof(T);
		uint floatwidth = size / 4;
		uint index = shader->propertyMap[name];

		if (floatwidth == 0)
		{
			floatwidth = 1;
		}

		for (uint i = 0; i < floatwidth; i++)
		{
			uint index = shader->propertyMap[name];
			shader->data[index + i] = val[i];
		}

	}
	else
	{
#ifdef DEBUG
		Debug::LogError("[Material] Attempted to set a property value that doesn't exist!");
#endif
	}
}

template<typename T>
void Material::SetPropertyValue(std::string name, T* val)
{
	// TODO: Check if the value type and T are the same
	if (shader->propertyMap.find(name) != shader->propertyMap.end())
	{
		size_t size = sizeof(T);
		uint floatwidth = size / 4;
		uint index = shader->propertyMap[name];

		if (floatwidth == 0)
		{
			floatwidth = 1;
		}

		for (uint i = 0; i < floatwidth; i++)
		{
			uint index = shader->propertyMap[name];
			// TODO: Watch this
			shader->data[index + i] = val[0][i];
		}

	}
	else
	{
#ifdef DEBUG
		Debug::LogError("[Material] Attempted to set a property value that doesn't exist!");
#endif
	}
}

template<>
void Material::SetPropertyValue<float>(std::string name, float val)
{
	// TODO: Check if the value type and T are the same
	if (shader->propertyMap.find(name) != shader->propertyMap.end())
	{
		uint index = shader->propertyMap[name];

		shader->data[index] = val;
	}
	else
	{
#ifdef DEBUG
		Debug::LogError("[Material] Attempted to set a property value that doesn't exist!");
#endif
	}
}

template<>
void Material::SetPropertyValue<Texture2D>(std::string name, Texture2D* tex)
{
	if (shader->textureMap.find(name) != shader->textureMap.end())
	{
		uint index = shader->textureMap[name];
		shader->textures[index] = tex;
	}
	else
	{
#ifdef DEBUG
		Debug::LogError("[Material] Attempted to set a property value that doesn't exist!");
#endif
	}
}

template void Material::SetPropertyValue<Vector2>(std::string name, Vector2 val);
template void Material::SetPropertyValue<Vector3>(std::string name, Vector3 val);
template void Material::SetPropertyValue<Vector4>(std::string name, Vector4 val);
template void Material::SetPropertyValue<Color>(std::string name, Color val);
template void Material::SetPropertyValue<Matrix>(std::string name, Matrix val);

void Material::InitializeStatic()
{
	Default = new Material(Shader::Default);

	Default->SetPropertyValue<Color>("tint", Color::Grey7);
	Default->SetPropertyValue<float>("roughness", 1.0f);
	Default->SetPropertyValue<float>("metalness", 0.0f);
}

void Material::Bind()
{
	shader->Bind();	

	SetTextures();
	UpdateAndSetBuffer();	
}

void Material::SetTextures()
{
	for (uint i = 0; i < shader->textures.size(); i++)
	{
		if (Texture2D* t = shader->textures[i])
		{
			t->Bind(i);
		}
	}
}

void Material::UpdateAndSetBuffer()
{
	float* fp = &shader->data[0];

	GraphicsDevice::GetDeviceContext()->UpdateSubresource(propertyBuffer, 0, 0, fp, 0, 0);

	GraphicsDevice::GetDeviceContext()->VSSetConstantBuffers(PER_MATERIAL_SLOT, 1, &propertyBuffer);
	GraphicsDevice::GetDeviceContext()->HSSetConstantBuffers(PER_MATERIAL_SLOT, 1, &propertyBuffer);
	GraphicsDevice::GetDeviceContext()->DSSetConstantBuffers(PER_MATERIAL_SLOT, 1, &propertyBuffer);
	GraphicsDevice::GetDeviceContext()->GSSetConstantBuffers(PER_MATERIAL_SLOT, 1, &propertyBuffer);
	GraphicsDevice::GetDeviceContext()->PSSetConstantBuffers(PER_MATERIAL_SLOT, 1, &propertyBuffer);
	GraphicsDevice::GetDeviceContext()->CSSetConstantBuffers(PER_MATERIAL_SLOT, 1, &propertyBuffer);
}

NS_END