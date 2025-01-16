#include "PlayerUtilities.h"

void SetRaycastedObject(
	std::weak_ptr<IGameObject> raycastedObject, 
	std::weak_ptr<IGameObject> target, 
	std::unique_ptr<Color> color
)
{
	if (raycastedObject.lock() != nullptr &&
		raycastedObject.lock() != target.lock()
		) {
		if (target.lock() != nullptr) {
			target.lock()->GetMaterial().lock()->SetDiffuse(Color(1, 1, 1));
		}

		target = raycastedObject;
		target.lock()->GetMaterial().lock()->SetDiffuse(*color);
	}
}
