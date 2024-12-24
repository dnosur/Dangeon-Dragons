#include "Ray.h"
#include "../functions.h"

Ray::Ray(Coord* origin, Coord* direction, float rayWidth)
{
	this->origin = origin;
	this->direction = direction;
	this->rayWidth = rayWidth;

	raySize = CalculateDistanceRef(*origin, *direction);
}
