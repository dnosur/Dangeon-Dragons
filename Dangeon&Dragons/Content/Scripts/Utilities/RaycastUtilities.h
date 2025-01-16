#pragma once
#include "../../../Dodge/raycast/Ray.h"
#include <memory>
<<<<<<< Updated upstream
std::unique_ptr<Ray> CreateRayToTarget(
	Coord* origin, class Pawn* target, 
=======

std::unique_ptr<Ray> CreateRayToTarget(
	Coord* origin, class Pawn* target,
>>>>>>> Stashed changes
	float rayWidth = 1.0f
);