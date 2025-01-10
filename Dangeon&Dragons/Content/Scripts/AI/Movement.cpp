#include "Movement.h"

Movement::Movement()
{
    complete = false;
    title = nullptr;

	action = Actions::Idle;
	direction = Directions::DOWN;
	animation = nullptr;
}

Movement::Movement(
    const char* title, Directions direction, Actions action, 
    IAnimation* animation, Coord position)
{
	copyStr(title, this->title);
	complete = false;

	this->direction = direction;
	this->action = action;
	this->animation = std::unique_ptr<IAnimation>(animation);
	this->position = position;
}
