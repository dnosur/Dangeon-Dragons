#include "RaycastUtilities.h"
#include "../../../Dodge/raycast/RayFactory.h"
#include "../Characters/Player/Player.h"

std::unique_ptr<Ray> CreateRayToTarget(Coord* origin, class Pawn* target, float rayWidth)
{
    if (Player* player = dynamic_cast<Player*>(target)) {
        return RayFactory::CreateRay(
            std::move(std::make_unique<Coord>(*origin)),
            std::move(std::make_unique<Coord>(player->GetStartPos())),
            rayWidth
        );
    }
    return RayFactory::CreateRay(
        std::move(std::make_unique<Coord>(*origin)),
        std::move(std::make_unique<Coord>(target->GetPos())),
        rayWidth
    );
}