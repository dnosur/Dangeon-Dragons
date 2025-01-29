#pragma once
#include "../Characters/Player/Player.h"
#include "../../../Dodge/raycast/RayFactory.h"

void SetRaycastedObject(
	std::weak_ptr<IGameObject> raycastedObject, 
	std::weak_ptr<IGameObject> target, 
	std::unique_ptr<Color> color
);