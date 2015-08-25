#include "Sampler.hpp"

#include "GraphicsDevice.hpp"

NS_BEGIN

Sampler* Sampler::ClampLinear;
Sampler* Sampler::ClampPoint;
Sampler* Sampler::ClampAnisotropic;
Sampler* Sampler::WrapLinear;
Sampler* Sampler::WrapPoint;
Sampler* Sampler::WrapAnisotropic;

Sampler::Sampler(AddressType addressType, FilterType filterType, ComparisonType comparisonType):
addressType(addressType),
filterType(filterType),
comparisonType(comparisonType)
{
	D3D11_SAMPLER_DESC sd;
	ZeroMemory(&sd, sizeof(D3D11_SAMPLER_DESC));

	sd.MinLOD = 0;
	sd.MaxLOD = 0;
	sd.MaxAnisotropy = 1;

	switch (addressType)
	{
	case AddressType::Clamp:
		sd.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		sd.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		sd.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		break;
	case AddressType::Wrap:
		sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		break;
	}

	switch (filterType)
	{
	case FilterType::Point:
		if (comparisonType == ComparisonType::None)
		{
			sd.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		}
		else
		{
			sd.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_POINT;
		}
		break;
	case FilterType::Linear:
		if (comparisonType == ComparisonType::None)
		{
			sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		}
		else
		{
			sd.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
		}		
		break;
	case FilterType::Anisotropic:
		if (comparisonType == ComparisonType::None)
		{
			sd.Filter = D3D11_FILTER_ANISOTROPIC;
		}
		else
		{
			sd.Filter = D3D11_FILTER_COMPARISON_ANISOTROPIC;
		}		
		break;
	}

	switch (comparisonType)
	{
	case ComparisonType::None:
		sd.ComparisonFunc = D3D11_COMPARISON_NEVER;
		break;
	case ComparisonType::Less:
		sd.ComparisonFunc = D3D11_COMPARISON_LESS;
		break;
	case ComparisonType::LessEqual:
		sd.ComparisonFunc = D3D11_COMPARISON_LESS_EQUAL;
		break;
	case ComparisonType::Equal:
		sd.ComparisonFunc = D3D11_COMPARISON_EQUAL;
		break;
	case ComparisonType::GreaterEqual:
		sd.ComparisonFunc = D3D11_COMPARISON_GREATER_EQUAL;
		break;
	case ComparisonType::Greater:
		sd.ComparisonFunc = D3D11_COMPARISON_GREATER;
		break;
	case ComparisonType::Always:
		sd.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		break;
	}

	GraphicsDevice::GetDevice()->CreateSamplerState(&sd, &sampler);

}

Sampler::~Sampler()
{}

void Sampler::InitializeStatic()
{
	ClampLinear = new Sampler(AddressType::Clamp, FilterType::Linear);
	ClampPoint = new Sampler(AddressType::Clamp, FilterType::Point);
	ClampAnisotropic = new Sampler(AddressType::Clamp, FilterType::Anisotropic);
	WrapLinear = new Sampler(AddressType::Wrap, FilterType::Linear);
	WrapPoint = new Sampler(AddressType::Wrap, FilterType::Point);
	WrapAnisotropic = new Sampler(AddressType::Wrap, FilterType::Anisotropic);
}

void Sampler::Bind(uint slot)
{
	GraphicsDevice::GetDeviceContext()->VSSetSamplers(slot, 1, &sampler);
	GraphicsDevice::GetDeviceContext()->PSSetSamplers(slot, 1, &sampler);
}

NS_END
