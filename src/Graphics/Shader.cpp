#include "Shader.hpp"

#include "GraphicsDevice.hpp"
#include <d3dcompiler.h>
#include "../Math/Math.hpp"

NS_BEGIN

Shader* Shader::Default;

Shader::Shader():
initialized(false)
{}

Shader::~Shader()
{
	DELETECOM(vertexShader);
	DELETECOM(hullShader);
	DELETECOM(domainShader);
	DELETECOM(geometryShader);
	DELETECOM(pixelShader);
	DELETECOM(computeShader);
}

void Shader::Initialize()
{

}

void Shader::Shutdown()
{
	delete Default;
}

bool Shader::LoadFromFile(std::string filepath, ShaderType sType)
{
	ID3DBlob* fileToBlob;

	std::wstring temp = std::wstring(filepath.begin(), filepath.end());
	HRESULT hr = D3DReadFileToBlob(temp.c_str(), &fileToBlob);

	if (hr != S_OK)
	{
#ifdef DEBUG
		Debug::LogError("[Shader] Could not compile shader.");
#endif
		return false;
	}

	switch (sType)
	{
	case Vertex:
		GraphicsDevice::GetDevice()->CreateVertexShader(fileToBlob->GetBufferPointer(), fileToBlob->GetBufferSize(), NULL, &vertexShader);
		break;
	case Hull:
		GraphicsDevice::GetDevice()->CreateHullShader(fileToBlob->GetBufferPointer(), fileToBlob->GetBufferSize(), 0, &hullShader);
		break;
	case Domain:
		GraphicsDevice::GetDevice()->CreateDomainShader(fileToBlob->GetBufferPointer(), fileToBlob->GetBufferSize(), NULL, &domainShader);
		break;
	case Geometry:
		GraphicsDevice::GetDevice()->CreateGeometryShader(fileToBlob->GetBufferPointer(), fileToBlob->GetBufferSize(), NULL, &geometryShader);
		break;
	case Pixel:
		GraphicsDevice::GetDevice()->CreatePixelShader(fileToBlob->GetBufferPointer(), fileToBlob->GetBufferSize(), NULL, &pixelShader);
		break;
	case Compute:
		GraphicsDevice::GetDevice()->CreateComputeShader(fileToBlob->GetBufferPointer(), fileToBlob->GetBufferSize(), NULL, &computeShader);
		break;
	}

	return true;
}

template<typename T>
void Shader::AddProperty(std::string name)
{
	if (propertyMap.find(name) == propertyMap.end())
	{
		// Store its index
		propertyMap[name] = data.size();
		size_t size = sizeof(T);
		uint floatwidth = size / 4;

#if DEBUG
		if ((size % 4) != 0)
		{
			Debug::Log("[Shader] Possible problem, check this out");
		}
		if (floatwidth == 0)
		{
			Debug::LogError("Shader] Major issue in addproperty, fix it");
			return;
		}
#endif
		T val;
		for (uint i = 0; i < floatwidth; i++)
		{
			data.push_back(val[i]);
		}
	}
	else
	{
#ifdef DEBUG
		Debug::LogError("[Shader] Attempted to add a property name that already exists!");
#endif
	}
}

template<>
void Shader::AddProperty<float>(std::string name)
{
	if (propertyMap.find(name) == propertyMap.end())
	{
		// Store its index
		propertyMap[name] = data.size();
		float val;

		data.push_back(val);
	}
	else
	{
#ifdef DEBUG
		Debug::LogError("[Shader] Attempted to add a property name that already exists!");
#endif
	}
}


template<>
void Shader::AddProperty<Texture2D>(std::string name)
{
	if (textureMap.find(name) == textureMap.end())
	{
		// Store its index
		textureMap[name] = textures.size();

		// Push back an empty texture
		textures.push_back(0);
	}
	else
	{
#ifdef DEBUG
		Debug::LogError("[Shader] Attempted to add a property name that already exists!");
#endif
	}
}

template void Shader::AddProperty<Vector2>(std::string name);
template void Shader::AddProperty<Vector3>(std::string name);
template void Shader::AddProperty<Vector4>(std::string name);
template void Shader::AddProperty<Color>(std::string name);
template void Shader::AddProperty<Matrix>(std::string name);

void Shader::InitializeStatic()
{
	Default = new Shader();
	Default->LoadFromFile("Shaders/DefaultVertex.cso", Vertex);
	Default->LoadFromFile("Shaders/DefaultPixel.cso", Pixel);

	Default->AddProperty<Color>("tint");
	Default->AddProperty<float>("roughness");
	Default->AddProperty<float>("metalness");

	Default->AddProperty<Texture2D>("diffuse");
	Default->AddProperty<Texture2D>("normal");
	Default->AddProperty<Texture2D>("metalness");
}

void Shader::Bind()
{
	GraphicsDevice::GetDeviceContext()->VSSetShader(vertexShader, 0, 0);
	GraphicsDevice::GetDeviceContext()->HSSetShader(hullShader, 0, 0);
	GraphicsDevice::GetDeviceContext()->DSSetShader(domainShader, 0, 0);
	GraphicsDevice::GetDeviceContext()->GSSetShader(geometryShader, 0, 0);
	GraphicsDevice::GetDeviceContext()->PSSetShader(pixelShader, 0, 0);
	GraphicsDevice::GetDeviceContext()->CSSetShader(computeShader, 0, 0);
}


NS_END