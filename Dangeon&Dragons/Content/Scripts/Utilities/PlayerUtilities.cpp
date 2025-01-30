#include "PlayerUtilities.h"

void SetRaycastedObject(
	std::weak_ptr<IGameObject> raycastedObject, 
	std::weak_ptr<IGameObject> target, 
	std::unique_ptr<Color> color
)
{
	std::shared_ptr<IGameObject> _raycastedObject = raycastedObject.lock();
	std::shared_ptr<IGameObject> _target = target.lock();

	if (_raycastedObject != nullptr &&
		_raycastedObject != _target
	) {
		if (_target != nullptr) {
			_target->GetMaterial().lock()->SetDiffuse(Color(1, 1, 1));
		}

		target = raycastedObject;
		if (_target && _target->GetMaterial().lock()) {
			_target->GetMaterial().lock()->SetDiffuse(*color);
		}
	}
}
