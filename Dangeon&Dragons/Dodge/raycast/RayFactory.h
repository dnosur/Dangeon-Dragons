#pragma once
#include "Ray.h"
#include "../pawn/Pawn.h"

static class RayFactory
{
public:
	static std::unique_ptr<Ray> CreateRay(Coord* origin, Coord* direction, float rayWidth = 1.0f);
	static std::unique_ptr<Ray> CreateRay(
		Coord* origin, Directions* direction,
		float raySize, float rayWidth = 1.0f
	);

	static std::unique_ptr<Ray> CreatePawnDirectionRay(
		class Pawn* pawn,
		float raySize = 1.0f, float rayWidth = 1.0f
	);
};