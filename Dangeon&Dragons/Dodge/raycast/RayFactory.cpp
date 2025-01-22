#include "RayFactory.h"

std::unique_ptr<Ray> RayFactory::CreateRay(
	std::unique_ptr<Coord> origin,
	std::unique_ptr<Coord> direction,
	float rayWidth
)
{
	if (origin == nullptr || direction == nullptr) {
		return nullptr;
	}

	return std::make_unique<Ray>(std::move(origin), std::move(direction), rayWidth);
}

std::unique_ptr<Ray> RayFactory::CreateRay(
	std::unique_ptr<Coord> origin,
	std::unique_ptr<Directions> direction,
	float raySize, 
	float rayWidth
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

	return std::make_unique<Ray>(
		std::move(origin),
		std::move(std::make_unique<Coord>(*origin + dir)),
		rayWidth
	);
}

std::unique_ptr<Ray> RayFactory::CreatePawnDirectionRay(
	class Pawn*& pawn,
	float raySize, float rayWidth)
{
	return CreateRay(
		std::make_unique<Coord>(
			pawn->GetPos()
		), 
		std::make_unique<Directions>(
			pawn->GetMoveDirection()
		),
		raySize, rayWidth
	);
}