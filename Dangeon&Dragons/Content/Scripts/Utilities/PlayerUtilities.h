#pragma once
#include "../Characters/Player/Player.h"
#include "../../../Dodge/raycast/RayFactory.h"

<<<<<<< Updated upstream
void SetRaycastedObject(std::shared_ptr<IGameObject>& raycastedObject, std::shared_ptr<IGameObject>& target, Color* color);
=======
void SetRaycastedObject(
	std::weak_ptr<IGameObject> raycastedObject, 
	std::weak_ptr<IGameObject> target, 
	std::unique_ptr<Color> color
);
>>>>>>> Stashed changes
