#include "Ray.h"
#include "../functions.h"

Ray::Ray(std::unique_ptr<Coord> origin, std::unique_ptr<Coord> direction, float rayWidth)
{
	this->origin = std::move(origin);
	this->direction = std::move(direction);
	this->rayWidth = rayWidth;

	raySize = CalculateDistanceRef(*this->origin, *this->direction);
}
