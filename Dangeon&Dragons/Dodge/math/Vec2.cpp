#include "Vec2.h"

Vec2::Vec2() 
    : x(0), y(0) {}

Vec2::Vec2(float x, float y)
    : x(x), y(y) {}

Vec2::Vec2(Coord coord): x(coord.X), y(coord.Y)
{
}

Vec2::Vec2(Size size): x(size.width), y(size.height)
{
}

bool Vec2::operator==(const Vec2& other) const
{
	return other.x == x && other.y == y;
}

bool Vec2::operator!=(const Vec2& other) const
{
	return !(*this == other);
}

bool Vec2::operator==(const Coord& other) const
{
	return other.X == x && other.Y == y;
}

bool Vec2::operator!=(const Coord& other) const
{
	return !(*this == other);
}

Vec2 Vec2::operator-(const Vec2& other) const
{
    return Vec2(x - other.x, y - other.y);
}

Vec2 Vec2::operator/(float value) const
{
    return Vec2(x / value, y / value);
}

Vec2 Vec2::operator=(const Vec2& other)
{
    if (this != &other) {
		x = other.x;
		y = other.y;
	}
	return *this;
}

Vec2 Vec2::operator=(const Coord& other)
{
	x = other.X;
	y = other.Y;
	return *this;
}
