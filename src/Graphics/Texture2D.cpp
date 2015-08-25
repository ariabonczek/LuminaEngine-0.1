#include "Texture2D.hpp"

#include "GraphicsDevice.hpp"

NS_BEGIN

Texture2D::Texture2D(uint width, uint height, bool renderTexture, Sampler* sampler) :
width(width),
height(height),
sampler(sampler)
{
	Resource::Resource();

	assert(width > 0 && height > 0);

	ID3D11Texture2D* texture;
	HRESULT hr;

	// Create the texture and render target view
	D3D11_TEXTURE2D_DESC td;
	ZeroMemory(&td, sizeof(D3D11_TEXTURE2D_DESC));

	td.Width = width;
	td.Height = height;
	td.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	td.Usage = D3D11_USAGE_DEFAULT;
	if (renderTexture)
		td.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	else
		td.BindFlags = D3D11_BIND_SHADER_RESOURCE;

	td.MipLevels = 1;
	td.ArraySize = 1;
	td.SampleDesc.Count = 1;

	hr = GraphicsDevice::GetDevice()->CreateTexture2D(&td, 0, &texture);

	// Create the shader resource view
	D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
	ZeroMemory(&srvd, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));

	srvd.Format = td.Format;
	srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvd.Texture2D.MipLevels = 1;

	hr = GraphicsDevice::GetDevice()->CreateShaderResourceView(texture, &srvd, &srv);

	DELETECOM(texture);
}

Texture2D::Texture2D(Image& imageData, bool renderTexture, Sampler* sampler) :
width(imageData.width),
height(imageData.height),
sampler(sampler)
{
	Resource::Resource();

	ID3D11Texture2D* texture;
	HRESULT hr;

	// Create the texture

	D3D11_TEXTURE2D_DESC td;
	ZeroMemory(&td, sizeof(D3D11_TEXTURE2D_DESC));

	td.Width = imageData.width;
	td.Height = imageData.height;
	td.ArraySize = 1;
	td.SampleDesc.Count = 1;
	td.SampleDesc.Quality = 0;
	td.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	
	renderTexture ?
		td.MipLevels = 0 :
		td.MipLevels = 1;

	renderTexture ?
		td.Usage = D3D11_USAGE_DYNAMIC :
		td.Usage = D3D11_USAGE_DEFAULT;

	renderTexture ?
		td.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE :
		td.BindFlags = D3D11_BIND_SHADER_RESOURCE;

	UINT rowpitch = 4 * width;
	UINT imagesize = rowpitch * height;

	// Copy the memory
	std::unique_ptr<uint8_t[]> temp(new uint8_t[imagesize]);

	// May want to put this in a different function i.e. CopyPixels
	if (imageData.components == 4)
	{
		std::memcpy(temp.get(), imageData.data, imagesize * sizeof(uint8_t));
	}
	else if (imageData.components == 3)
	{
		// foreach pixel
		for (ULONG i = 0; i < imageData.width * imageData.height; i++)
		{
			// copy the rgb
			for (int j = 0; j < 3; j++)
			{
				temp.get()[i * 4 + j] = imageData.data[i * 3 + j];
			}
			// set alpha to 1
			temp.get()[i * 4 + 3] = 1.0f;
		}
	}

	D3D11_SUBRESOURCE_DATA srd;
	ZeroMemory(&srd, sizeof(D3D11_SUBRESOURCE_DATA));
	srd.pSysMem = temp.get();
	srd.SysMemPitch = rowpitch;
	srd.SysMemSlicePitch = imagesize;

	hr = GraphicsDevice::GetDevice()->CreateTexture2D(&td, &srd, &texture);

	// Create the shader resource view
	D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
	ZeroMemory(&srvd, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));

	srvd.Format = td.Format;
	srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvd.Texture2D.MipLevels = 1;

	hr = GraphicsDevice::GetDevice()->CreateShaderResourceView(texture, &srvd, &srv);

	// Update the subresource data
	if (!renderTexture)
	{
		GraphicsDevice::GetDeviceContext()->UpdateSubresource(texture,
			0, nullptr, temp.get(), rowpitch, imagesize);
	}
	DELETECOM(texture);
}

Texture2D::~Texture2D()
{
	DELETECOM(srv);
}

void Texture2D::Bind(uint slot)
{
	// TODO: Batch samplers
	if (sampler)
	{
		sampler->Bind(slot);
	}
	// TODO: If possible only bind to used shaders?
	if (srv)
	{
		GraphicsDevice::GetDeviceContext()->VSSetShaderResources(slot, 1, &srv);
		GraphicsDevice::GetDeviceContext()->PSSetShaderResources(slot, 1, &srv);
	}
}

Texture2D::operator ID3D11ShaderResourceView*()const
{
	return srv;
}

NS_END