#pragma once
#include "AIStrategy.h"

#include <memory>

class Pawn;

class AIContext :
    public AIStrategy
{
    std::unique_ptr<AIStrategy> strategy;
protected:

public:
    explicit AIContext(std::unique_ptr<AIStrategy> strategy);

    void SetStrategy(std::unique_ptr<AIStrategy> strategy);

    bool Invoke(class Pawn* pawn, AIContext* sender = nullptr);
};