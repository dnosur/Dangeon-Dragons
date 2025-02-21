#pragma once
#include "../../../../Dodge/Directions.h"
#include "../../../../Dodge/animator/IAnimation.h"
#include "../../.../../../../Dodge/pawn/Actions.h"

#include "../Algorithms/AIContext.h"

struct Movement
{
	std::string_view title;

	bool complete;

	Directions direction;
	Actions action;

	std::shared_ptr<IAnimation> animation;
	std::unique_ptr<AIContext> aiContext;

	Coord position;

	Movement();
	Movement(
		std::string_view title, Directions direction, Actions action,
		std::shared_ptr<IAnimation> animation, Coord position, 
		std::unique_ptr<AIContext> aiContext = nullptr
	);
}; 