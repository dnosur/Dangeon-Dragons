#include "Movement.h"

Movement::Movement()
{
    complete = false;

	action = Actions::Idle;
	direction = Directions::DOWN;
	animation = nullptr;
}

Movement::Movement(
    std::string title, Directions direction, Actions action, 
    IAnimation* animation, Coord position)
{
	this->title = title;
	complete = false;

	this->direction = direction;
	this->action = action;
	this->animation = animation;
	this->position = position;
}
