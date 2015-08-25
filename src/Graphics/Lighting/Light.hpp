#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "../../Config.hpp"

#include "../../Objects/Component.hpp"
#include "../Color.hpp"
#include "../../Math/Math.hpp"

NS_BEGIN

enum class ShadowType
{
	None,
	Hard,
	Soft
};

/// <summary>
/// Base class for all Lumina lights
/// </summary>
class Light : public Component
{
public:
	Light(Color color = Color(), float intensity = 1.0f);
	virtual ~Light();

	void Initialize();

	Color GetColor()const;
	float GetIntensity()const;
	bool GetHasShadows()const;

	void SetColor(Color color);
	void SetIntensity(float intensity);
	void SetShadows(ShadowType shadowType);
protected:
	Color color;
	float intensity;
	ShadowType shadowType;
};


NS_END

#endif