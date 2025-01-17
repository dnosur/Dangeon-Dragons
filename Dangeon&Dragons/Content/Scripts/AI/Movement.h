#pragma once
#include "../../../Dodge/Directions.h"
#include "../../../Dodge/animator/IAnimation.h"
#include "../../../Dodge/pawn/Actions.h"

struct Movement
{
	std::string title;

	bool complete;

	Directions direction;
	Actions action;

	std::shared_ptr<IAnimation> animation;

	Coord position;

	Movement();
	Movement(
		std::string title, Directions direction, Actions action, 
		std::shared_ptr<IAnimation> animation, Coord position
	);
}; 