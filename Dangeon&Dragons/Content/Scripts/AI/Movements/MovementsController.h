#pragma once
#include "Movement.h"

#include "../Algorithms/AIContext.h"

class MovementsController
{
	std::vector<std::unique_ptr<Movement>> movements;
	int movementIndex;
public:
	MovementsController();
	~MovementsController() = default;

	void AddMovement(std::unique_ptr<Movement> movement);

	void UseOffset(Coord* offset);
	void MakeNext(class Pawn*& pawn);

	void Clear();

	const bool IsEmpty();

	int Size();

	bool IsComplete();

	std::vector<std::unique_ptr<Movement>>::iterator begin();
	std::vector<std::unique_ptr<Movement>>::iterator end();

	Movement* operator[](int index);
};