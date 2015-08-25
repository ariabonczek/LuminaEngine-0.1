#ifndef POINT_LIGHT_HPP
#define POINT_LIGHT_HPP

#include "../../Config.hpp"

#include "Light.hpp"

NS_BEGIN

class PointLight : public Light
{
public:
	PointLight(float range = 10.0f);
	PointLight(Color color, float intensity, float range);
	~PointLight();

	float GetRange()const;

	void SetRange(float range);

private:
	float range;
};

NS_END

#endif