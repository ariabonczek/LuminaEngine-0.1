#include "DirectionalLight.hpp"

NS_BEGIN

DirectionalLight::DirectionalLight():
Light()
{}

DirectionalLight::DirectionalLight(Color color, float intensity):
Light(color, intensity)
{}

DirectionalLight::~DirectionalLight()
{}


NS_END