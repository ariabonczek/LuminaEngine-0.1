#include "Geometry.hpp"

NS_BEGIN

Rectangle::Rectangle() :
x(0), y(0), width(0), height(0)
{}
Rectangle::Rectangle(int x, int y, uint width, uint height) :
x(x), y(y), width(width), height(height)
{}
Rectangle::Rectangle(Vector2 position, Vector2 size) :
x((int)position.x), y((int)position.y), width((uint)size.x), height((uint)size.y)
{}

Vector2 Rectangle::Position()const { return Vector2((float)x, (float)y); }
Vector2 Rectangle::Size()const { return Vector2((float)width, (float)height); }
Vector2 Rectangle::Center()const { return Vector2(x + width / 2.0f, y + height / 2.0f); }

bool Rectangle::Contains(Vector2 v) { return ((((x <= v.x) && (v.x < (x + width))) && ((y <= v.y)) && (v.y < (y + height)))); }
// TODO: Finish Rectangle Functions
//bool Rectangle::Contains(int x, int y){}
//bool Rectangle::Contains(float x, float y){}
//bool Rectangle::Contains(Rectangle r){}
//
//void Rectangle::Inflate(int x, int y){}
//void Rectangle::Inflate(float x, float y){}
//
bool Rectangle::Intersects(Rectangle r)
{
	return (r.x < x + (int)width &&
		x < r.x + (int)r.width &&
		r.y < y + (int)height &&
		y < r.y + (int)r.height
		);
}
bool Rectangle::Intersects(Rectangle r1, Rectangle r2)
{
	return (r1.x < r2.x + (int)r2.width &&
		r2.x < r1.x + (int)r1.width &&
		r1.y < r2.y + (int)r2.height &&
		r2.y < r1.y + (int)r1.height
		);
}
//
//void Rectangle::Offset(Vector2 v){}
//void Rectangle::Offset(int x, int y){}
//void Rectangle::Offset(float x, float y){}
//
//Rectangle Rectangle::Union(Rectangle r1, Rectangle r2){}
//

NS_END