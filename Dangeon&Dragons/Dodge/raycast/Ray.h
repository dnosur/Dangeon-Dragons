#pragma once
#include "../Coord.h"

#include <memory>

struct Ray
{
	std::unique_ptr<Coord> origin;
	std::unique_ptr<Coord> direction;

	float rayWidth;
	float raySize;
	Ray(
		std::unique_ptr<Coord> origin, 
		std::unique_ptr<Coord> direction, 
		float rayWidth = 1.0f
	);
};