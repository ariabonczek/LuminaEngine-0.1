#ifndef COLOR_HPP
#define COLOR_HPP

#include "../Config.hpp"

NS_BEGIN

// TODO: Add more functionality to the color struct
// Maybe make color a class and have a separate struct for colordata?

class Color
{
public:
	float r, g, b, a;

	Color();
	Color(float r, float g, float b, float a);

	static Color Red;
	static Color Green;
	static Color Blue;
	static Color White;
	static Color Black;
	static Color Grey7;
	static Color Gray7;

	float operator[](int index);
private:
};

NS_END

#endif