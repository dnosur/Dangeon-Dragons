#pragma once
#include "../../../Dodge/raycast/Ray.h"

Ray* CreateRayToTarget(
	Coord* origin, class Pawn* target, 
	float rayWidth = 1.0f
);