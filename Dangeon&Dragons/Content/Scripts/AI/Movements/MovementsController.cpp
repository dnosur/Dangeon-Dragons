#include "MovementsController.h"
#include "../Algorithms/WanderContext.h"

#include "../../../../Dodge/pawn/Pawn.h"

MovementsController::MovementsController()
	: movementIndex(0)
{
}

void MovementsController::AddMovement(std::unique_ptr<Movement> movement)
{
	movements.push_back(std::move(movement));
}

void MovementsController::UseOffset(Coord* offset)
{
	for (std::unique_ptr<Movement>& movement : movements) {
		if (!movement) continue;
		movement->position += *offset;
	}
	offset->Set(0, 0);
}

void MovementsController::MakeNext(class Pawn*& pawn)
{
	if (IsComplete()) {
		Clear();
		return;
	}

	//UseOffset(pawn->GetOffset().GetOffset());

	std::unique_ptr<Movement> movement = std::move(movements[movementIndex]);

	pawn->SetAction(movement->action);
	pawn->SetMoveDirection(movement->direction);

	if (movement->aiContext && 
		!movement->aiContext->Invoke(pawn, movement->aiContext.get())) {
		movements[movementIndex] = std::move(movement);
		return;
	}

	pawn->SetPos(movement->position);
	movement->animation->Play();

	movement.reset();
	movementIndex++;
}

void MovementsController::Clear()
{
	movementIndex = 0;
	movements.clear();
}

const bool MovementsController::IsEmpty()
{
	return movements.empty();
}

int MovementsController::Size()
{
	return movements.size();
}

bool MovementsController::IsComplete()
{
	return movements.size() == movementIndex + 1;
}

std::vector<std::unique_ptr<Movement>>::iterator MovementsController::begin()
{
	return movements.begin();
}

std::vector<std::unique_ptr<Movement>>::iterator MovementsController::end()
{
	return movements.end();
}

Movement* MovementsController::operator[](int index)
{
	if (index >= movements.size()) return nullptr;
	return movements[index].get();
}
