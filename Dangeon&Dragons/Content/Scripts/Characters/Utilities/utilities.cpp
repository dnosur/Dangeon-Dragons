#include "utilities.h"

#include "../Enemys/Skeleton.h"
#include "../Player/Player.h"

bool IsSkeleton(class Pawn* pawn)
{
	return pawn->GetClassTypeId() == typeid(Skeleton);
}

bool IsPlayer(class Pawn* pawn)
{
	return pawn->GetClassTypeId() == typeid(Player);
}
