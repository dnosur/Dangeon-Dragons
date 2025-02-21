#pragma once
class Pawn;
class AIContext;

class AIStrategy
{
public:
	virtual ~AIStrategy() = default;
	virtual bool Invoke(class Pawn* pawn, AIContext* sender = nullptr) = 0;
};