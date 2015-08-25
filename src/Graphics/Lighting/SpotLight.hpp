#ifndef SPOT_LIGHT_HPP
#define SPOT_LIGHT_HPP

#include "../../Config.hpp"

#include "Light.hpp"

NS_BEGIN

class SpotLight : public Light
{
public:
	SpotLight(float range, float spot);
	SpotLight(Color color, float intensity, float range, float spot);
	~SpotLight();

	float GetRange()const;
	float GetSpot()const;

	void SetRange(float range);
	void SetSpot(float spot);

private:
	float range;
	float spotAngle;
};

NS_END

#endif