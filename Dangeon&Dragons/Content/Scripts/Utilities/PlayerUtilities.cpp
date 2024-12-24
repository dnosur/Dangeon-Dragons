#include "PlayerUtilities.h"

void SetRaycastedObject(IGameObject*& raycastedObject, IGameObject*& target, Color* color)
{
	if (raycastedObject != nullptr &&
		raycastedObject != target
		) {
		if (target != nullptr) {
			target->GetMaterial()->SetDiffuse(Color(1, 1, 1));
		}

		target = raycastedObject;
		target->GetMaterial()->SetDiffuse(*color);
	}
}
