#pragma once
#include "../../../Dodge/Directions.h"
#include "../../../Dodge/animator/IAnimation.h"
#include "../../../Dodge/pawn/Actions.h"

struct Movement
{
<<<<<<< Updated upstream
	char* title;
=======
	std::string_view title;
>>>>>>> Stashed changes

	bool complete;

	Directions direction;
	Actions action;

	IAnimation* animation;

	Coord position;

	Movement();
	Movement(
<<<<<<< Updated upstream
		const char* title, Directions direction, Actions action, 
		IAnimation* animation, Coord position
=======
		std::string_view title, Directions direction, Actions action,
		std::shared_ptr<IAnimation> animation, Coord position
>>>>>>> Stashed changes
	);
}; 