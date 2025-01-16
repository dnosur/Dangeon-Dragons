#pragma once
#include "Ray.h"
#include "../pawn/Pawn.h"

static class RayFactory
{
public:
	static std::unique_ptr<Ray> CreateRay(Coord* origin, Coord* direction, float rayWidth = 1.0f);
	static std::unique_ptr<Ray> CreateRay(
<<<<<<< Updated upstream
		Coord* origin, Directions* direction, 
=======
		Coord* origin, Directions* direction,
>>>>>>> Stashed changes
		float raySize, float rayWidth = 1.0f
	);

	static std::unique_ptr<Ray> CreatePawnDirectionRay(
<<<<<<< Updated upstream
		class Pawn* pawn, 
=======
		class Pawn* pawn,
>>>>>>> Stashed changes
		float raySize = 1.0f, float rayWidth = 1.0f
	);
};