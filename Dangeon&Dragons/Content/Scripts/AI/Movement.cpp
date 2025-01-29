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
<<<<<<< Updated upstream
    const char* title, Directions direction, Actions action, 
    IAnimation* animation, Coord position)
=======
    std::string_view title, Directions direction, Actions action,
	std::shared_ptr<IAnimation> animation, Coord position)
>>>>>>> Stashed changes
{
	copyStr(title, this->title);
	complete = false;

	this->direction = direction;
	this->action = action;
	this->animation = animation;
	this->position = position;
}
