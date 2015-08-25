#include "PointLight.hpp"

NS_BEGIN

PointLight::PointLight(float range):
Light(),
range(range)
{}

PointLight::PointLight(Color color, float intensity, float range):
Light(color, intensity),
range(range)
{} 

PointLight::~PointLight()
{}

float PointLight::GetRange()const
{
	return range;
}

void PointLight::SetRange(float range)
{
	this->range = range;
}

NS_END