#pragma once
#include "../Coord.h"

struct Ray
{
	Coord* origin;
	Coord* direction;

	float rayWidth;
	float raySize;

	Ray(Coord* origin, Coord* direction, float rayWidth = 1.0f);
};