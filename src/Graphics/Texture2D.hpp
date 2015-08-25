#ifndef TEXTURE2D_HPP
#define TEXTURE2D_HPP

#include "../Config.hpp"
#include "Image.hpp"
#include "../Utility/Resource.hpp"
#include "Sampler.hpp"

NS_BEGIN

class GraphicsDevice;

enum TextureFormat
{
	Greyscale,
	RGB,
	RGBA
};

class Texture2D : public Resource
{
public:
	Texture2D(uint width, uint height, bool renderTexture = false, Sampler* sampler = Sampler::ClampLinear);
	Texture2D(Image& imageData, bool renderTexture = false, Sampler* sampler = Sampler::ClampLinear);
	~Texture2D();

	void Bind(uint slot);

	operator ID3D11ShaderResourceView*()const;
private:
	uint width, height;
	TextureFormat format;

	Sampler* sampler;
	ID3D11ShaderResourceView* srv;
};

NS_END

#endif