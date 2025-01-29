#include "Sides.h"

Sides::Sides()
{
	left = 0;
	right = 0;
	top = 0;
	bottom = 0;
}

Sides::Sides(double left, double right, double top, double bottom):
	left(left), right(right), top(top), bottom(bottom)
{
}
