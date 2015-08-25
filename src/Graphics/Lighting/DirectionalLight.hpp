#ifndef DIRECTIONAL_LIGHT_HPP
#define DIRECTIONAL_LIGHT_HPP

#include "../../Config.hpp"

#include "Light.hpp"

NS_BEGIN

class DirectionalLight : public Light
{
public:
	DirectionalLight();
	DirectionalLight(Color color, float intensity);
	~DirectionalLight();
private:
};

NS_END

#endif