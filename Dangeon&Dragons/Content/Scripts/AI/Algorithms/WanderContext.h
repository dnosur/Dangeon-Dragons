#pragma once
#include "AIContext.h"

#include <thread>
#include <mutex>

#include "../Movements/MovementsController.h"

class WanderContext :
    public AIStrategy
{
    std::mutex pathMutex;
    bool findingPath;

    std::unique_ptr<MovementsController> movements;

    Coord GenerateRandomPosition(class Pawn* pawn, Coord center, float radius);

    bool FindPath(class Pawn* pawn, Coord start, Coord goal);

    std::vector<std::unique_ptr<Movement>> GetNeighbors(class Pawn*& pawn, Coord position);

    bool FindTarget();
public:
	WanderContext();
    bool Invoke(class Pawn* pawn, AIContext* sender = nullptr) override;
};