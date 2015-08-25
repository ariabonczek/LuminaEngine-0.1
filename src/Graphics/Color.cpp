#include "Color.hpp"

NS_BEGIN

Color Color::Red(1.0f, 0.0f, 0.0f, 1.0f);
Color Color::Green(0.0f, 1.0f, 0.0f, 1.0f);
Color Color::Blue(0.0f, 0.0f, 1.0f, 1.0f);
Color Color::White(1.0f, 1.0f, 1.0f, 1.0f);
Color Color::Black(0.0f, 0.0f, 0.0f, 1.0f);
Color Color::Grey7(0.7f, 0.7f, 0.7f, 1.0f);
Color Color::Gray7(0.7f, 0.7f, 0.7f, 1.0f);

Color::Color()
{}

Color::Color(float r, float g, float b, float a) :
r(r), g(g), b(b), a(a)
{}

float Color::operator[](int index)
{
	switch (index)
	{
	case 0:
		return r;
	case 1:
		return g;
	case 2:
		return b;
	case 3:
		return a;
	default:
		throw "[Color] IndexOutOfRange Exception";
	}
}

NS_END