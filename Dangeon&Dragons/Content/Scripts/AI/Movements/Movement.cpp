#include "Movement.h"

Movement::Movement()
{
    complete = false;

	action = Actions::Idle;
	direction = Directions::DOWN;

	animation = nullptr;
	aiContext = nullptr;
}

Movement::Movement(
    std::string_view title, Directions direction, Actions action,
	std::shared_ptr<IAnimation> animation, Coord position,
	std::unique_ptr<AIContext> aiContext)
{
	this->title = title;
	complete = false;

	this->direction = direction;
	this->action = action;
	this->animation = animation;
	this->position = position;

	this->aiContext = std::move(aiContext);
}
