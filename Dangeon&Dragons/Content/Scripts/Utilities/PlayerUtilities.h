#pragma once
#include "../Characters/Player/Player.h"
#include "../../../Dodge/raycast/RayFactory.h"

void SetRaycastedObject(std::shared_ptr<IGameObject>& raycastedObject, std::shared_ptr<IGameObject>& target, Color* color);