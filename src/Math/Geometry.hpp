#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include "../Config.hpp"

#include "Vector.hpp"

NS_BEGIN

// TODO: All this
	// Constructors
	// Intersections
	// Other witchcraft

struct Ray
{
	Vector3 origin, direction;
};

// TODO: Figure out better name scheme for objects like this
struct PlaneMath
{
	Vector3 normal;
	float distanceFromOrigin;
};

struct Rectangle
{
	int x, y;
	uint width, height;

	Rectangle();
	Rectangle(int x, int y, uint width, uint height);
	Rectangle(Vector2 position, Vector2 size);

	/// <summary>
	/// Position of the top left corner of the rectangle
	/// </summary>
	Vector2 Position()const;

	/// <summary>
	/// Size of the rectangle in width, height
	/// </summary>
	Vector2 Size()const;

	/// <summary>
	/// Returns a point in the center of the rectangle
	/// </summary>
	Vector2 Center()const;

	/// <summary>
	/// Returns true if v is within the rectangle
	/// </summary>
	bool Contains(Vector2 v);

	/// <summary>
	/// Returns true if point x, y is in the rectangle
	/// </summary>
	bool Contains(int x, int y);

	/// <summary>
	/// Returns true if point x, y is in the rectangle
	/// </summary>
	bool Contains(float x, float y);

	/// <summary>
	/// Returns true if Rectangle r is in the rectangle
	/// </summary>
	bool Contains(Rectangle r);

	/// <summary>
	/// Increases the size of the rectangle by x, y
	/// </summary>
	void Inflate(int x, int y);

	/// <summary>
	/// Increases the size of the rectangle by x, y
	/// </summary>
	void Inflate(float x, float y);

	/// <summary>
	/// Returns true if rectangle intersects Rectangle r
	/// </summary>
	bool Intersects(Rectangle r);

	/// <summary>
	/// Returns true if the two Rectangles intersect
	/// </summary>
	static bool Intersects(Rectangle r1, Rectangle r2);

	/// <summary>
	/// Moves the rectangle by v
	/// </summary>
	void Offset(Vector2 v);

	/// <summary>
	/// moves the rectangle by x, y
	/// </summary>
	void Offset(int x, int y);

	/// <summary>
	/// Moves the rectangle x, y
	/// </summary>
	void Offset(float x, float y);

	/// <summary>
	/// Returns a new rectangle containing both r1 and r2
	/// </summary>
	static Rectangle Union(Rectangle r1, Rectangle r2);
};

/// <summary>
/// 3D Rectangle, may be useful for octree
/// </summary>
struct Box
{
	Vector3 position;
	Vector3 size;
	Vector3 rotation;
};


NS_END

#endif