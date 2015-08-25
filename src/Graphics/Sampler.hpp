#ifndef SAMPLER_HPP
#define SAMPLER_HPP

#include "../Config.hpp"

NS_BEGIN

enum class AddressType
{
	Clamp,
	Wrap
};

enum class FilterType
{
	Point,
	Linear,
	Anisotropic
};

enum class ComparisonType
{
	None,
	Less,
	LessEqual,
	Equal,
	GreaterEqual,
	Greater,
	Always
};

class Sampler
{
public:
	Sampler(AddressType addressType, FilterType filterType, ComparisonType comparisonType = ComparisonType::None);
	~Sampler();

	static void InitializeStatic();

	static Sampler* ClampLinear;
	static Sampler* ClampPoint;
	static Sampler* ClampAnisotropic;
	static Sampler* WrapLinear;
	static Sampler* WrapPoint;
	static Sampler* WrapAnisotropic;

	void Bind(uint slot);

private:
	ID3D11SamplerState* sampler;

	AddressType addressType;
	FilterType  filterType;
	ComparisonType comparisonType;
};

NS_END

#endif