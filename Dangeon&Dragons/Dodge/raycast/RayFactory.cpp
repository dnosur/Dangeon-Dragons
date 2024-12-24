#include "RayFactory.h"

Ray* RayFactory::CreateRay(Coord* origin, Coord* direction, float rayWidth)
{
	if (origin == nullptr || direction == nullptr) {
		return nullptr;
	}

	return new Ray(origin, direction, rayWidth);
}

Ray* RayFactory::CreateRay(
	Coord* origin, Directions* direction,
	float raySize, float rayWidth
)
{
	Coord dir;

	if (*direction == Directions::UP) {
		dir.Y -= raySize;
	}

	if (*direction == Directions::DOWN) {
		dir.Y += raySize;
	}

	if (*direction == Directions::LEFT) {
		dir.X -= raySize;
	}

	if (*direction == Directions::RIGHT) {
		dir.X += raySize;
	}

	return new Ray(
		origin, new Coord(*origin + dir),
		rayWidth
	);
}

Ray* RayFactory::CreatePawnDirectionRay(
	class Pawn* pawn, 
	float raySize, float rayWidth)
{
	return CreateRay(
		new Coord(
			pawn->GetPos()
		), new Directions(
			pawn->GetMoveDirection()
		),
		raySize, rayWidth
	);
}
