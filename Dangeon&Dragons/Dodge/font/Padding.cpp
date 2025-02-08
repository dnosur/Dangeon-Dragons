#include "Padding.h"

Padding::Padding()
	: left(0), top(0), right(0), bottom(0) {}

Padding::Padding(float left, float top, float right, float bottom)
	: left(left), top(top), right(right), bottom(bottom) {}

void Padding::Use(float& x, float& y)
{
	x += left;
	x -= right;

	y += bottom;
	y -= top;
}

void Padding::Use(Coord& pos)
{
	pos.X += left;
	pos.X -= right;

	pos.Y += bottom;
	pos.Y -= top;
}
