#pragma once
#include "../../../Dodge/Directions.h"
#include "../../../Dodge/animator/IAnimation.h"
#include "../../../Dodge/pawn/Actions.h"

struct Movement
{
	char* title;

	bool complete;

	Directions direction;
	Actions action;

	std::unique_ptr<IAnimation> animation;

	Coord position;

	Movement();
	Movement(
		const char* title, Directions direction, Actions action, 
		IAnimation* animation, Coord position
	);
}; 