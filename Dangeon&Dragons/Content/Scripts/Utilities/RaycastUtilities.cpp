#include "RaycastUtilities.h"
#include "../../../Dodge/raycast/RayFactory.h"
#include "../Characters/Player/Player.h"

std::unique_ptr<Ray> CreateRayToTarget(Coord* origin, class Pawn* target, float rayWidth)
{
    if (Player* player = dynamic_cast<Player*>(target)) {
		return std::move(RayFactory::CreateRay(origin, new Coord(player->GetStartPos()), rayWidth));
    }
    return std::move(RayFactory::CreateRay(origin, new Coord(target->GetPos()), rayWidth));
}
