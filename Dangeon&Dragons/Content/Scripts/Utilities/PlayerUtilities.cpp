#include "PlayerUtilities.h"

void SetRaycastedObject(
	std::weak_ptr<IGameObject> raycastedObject, 
	std::weak_ptr<IGameObject> target, 
	std::unique_ptr<Color> color
)
{
	const std::shared_ptr<IGameObject>& _raycastedObject = raycastedObject.lock();
	const std::shared_ptr<IGameObject>& _target = target.lock();

	if (_raycastedObject != nullptr &&
		_raycastedObject != _target
	) {
		if (_target != nullptr) {
			_target->GetMaterial().lock()->SetDiffuse(Color(1, 1, 1));
		}

		target = raycastedObject;
		_target->GetMaterial().lock()->SetDiffuse(*color);
	}
}
