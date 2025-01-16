#include "RayFactory.h"

std::unique_ptr<Ray> RayFactory::CreateRay(Coord* origin, Coord* direction, float rayWidth)
{
	if (origin == nullptr || direction == nullptr) {
		return nullptr;
	}

	return std::move(std::unique_ptr<Ray>(new Ray(origin, direction, rayWidth)));
}

std::unique_ptr<Ray> RayFactory::CreateRay(
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

<<<<<<< Updated upstream
	return std::move (std::unique_ptr<Ray>(new Ray(
=======
	return std::move(std::unique_ptr<Ray>(new Ray(
>>>>>>> Stashed changes
		origin, new Coord(*origin + dir),
		rayWidth
	)));
}

std::unique_ptr<Ray> RayFactory::CreatePawnDirectionRay(
<<<<<<< Updated upstream
	class Pawn* pawn, 
=======
	class Pawn* pawn,
>>>>>>> Stashed changes
	float raySize, float rayWidth)
{
	return std::move(CreateRay(
		new Coord(
			pawn->GetPos()
		), new Directions(
			pawn->GetMoveDirection()
		),
		raySize, rayWidth
	));
<<<<<<< Updated upstream
}
=======
}
>>>>>>> Stashed changes
