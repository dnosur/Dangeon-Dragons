#include "PlayerUtilities.h"

void SetRaycastedObject(
<<<<<<< Updated upstream
	std::shared_ptr<IGameObject>& raycastedObject, 
	std::shared_ptr<IGameObject>& target, 
	Color* color
){
	if (raycastedObject != nullptr &&
		raycastedObject != target
=======
	std::weak_ptr<IGameObject> raycastedObject, 
	std::weak_ptr<IGameObject> target, 
	std::unique_ptr<Color> color
)
{
	if (raycastedObject.lock() != nullptr &&
		raycastedObject.lock() != target.lock()
>>>>>>> Stashed changes
		) {
		if (target.lock() != nullptr) {
			target.lock()->GetMaterial().lock()->SetDiffuse(Color(1, 1, 1));
		}

		target = raycastedObject;
		target.lock()->GetMaterial().lock()->SetDiffuse(*color);
	}
}
