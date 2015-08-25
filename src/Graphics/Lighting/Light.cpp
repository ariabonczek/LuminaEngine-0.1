#include "Light.hpp"

NS_BEGIN

Light::Light(Color color, float intensity) :
color(color),
intensity(intensity),
shadowType(ShadowType::None)
{}

Light::~Light()
{}

void Light::Initialize()
{

}

Color Light::GetColor()const
{
	return color;
}

float Light::GetIntensity()const
{
	return intensity;
}

// TODO: Support for hard and soft shadows (maybe? why tho?)
bool Light::GetHasShadows()const
{
	return !(shadowType == ShadowType::None);
}

void Light::SetColor(Color color)
{
	this->color = color;
}

void Light::SetIntensity(float intensity)
{
	this->intensity = intensity;
}

void Light::SetShadows(ShadowType shadowType)
{
	this->shadowType = shadowType;
}

NS_END