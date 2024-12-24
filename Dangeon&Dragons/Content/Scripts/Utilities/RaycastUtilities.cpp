#include "RaycastUtilities.h"
#include "../../../Dodge/raycast/RayFactory.h"
#include "../Characters/Player/Player.h"

Ray* CreateRayToTarget(Coord* origin, class Pawn* target, float rayWidth)
{
    if (Player* player = dynamic_cast<Player*>(target)) {
		return RayFactory::CreateRay(origin, new Coord(player->GetStartPos()), rayWidth);
    }
    return RayFactory::CreateRay(origin, new Coord(target->GetPos()), rayWidth);
}
