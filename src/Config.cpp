#include "Config.hpp"

float DegreesToRadians(float d)
{
	return PI * d / 180.0f;
}

float RadiansToDegrees(float r)
{
	return r * 180.0f / PI;
}