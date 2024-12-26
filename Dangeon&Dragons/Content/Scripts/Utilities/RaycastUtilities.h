#pragma once
#include "../../../Dodge/raycast/Ray.h"
#include <memory>
std::unique_ptr<Ray> CreateRayToTarget(
	Coord* origin, class Pawn* target, 
	float rayWidth = 1.0f
);