#include "Directions.h"
#include "Coord.h"

Directions GetDirection(Coord& direction)
{
	if (direction == Coord(1, 0)) {
		return Directions::RIGHT;
	}

	if (direction == Coord(-1, 0)) {
		return Directions::LEFT;
	}

	if (direction == Coord(0, 1)) {
		return Directions::DOWN;
	}

	if (direction == Coord(0, -1)) {
		return Directions::UP;
	}

	if (direction == Coord(1, 1)) {
		return Directions::DOWN;
	}

	if (direction == Coord(1, -1)) {
		return Directions::UP;
	}

	if (direction == Coord(-1, 1)) {
		return Directions::DOWN;
	}

	if (direction == Coord(-1, -1)) {
		return Directions::UP;
	}

	return Directions::DOWN;
}
