#include "SpotLight.hpp"

NS_BEGIN

SpotLight::SpotLight( float range, float spot):
Light(),
range(range),
spotAngle(spot)
{}

SpotLight::SpotLight(Color color, float intensity, float range, float spot):
Light(color, intensity),
range(range),
spotAngle(spot)
{}

SpotLight::~SpotLight()
{}

float SpotLight::GetRange()const
{
	return range;
}

float SpotLight::GetSpot()const
{
	return spotAngle;
}

void SpotLight::SetRange(float range)
{
	this->range = range;
}

void SpotLight::SetSpot(float spot)
{
	this->spotAngle = spot;
}

NS_END