#include "CollisionsController.h"

CollisionsController::CollisionsController()
{
}

CollisionsController::CollisionsController(std::vector<ICollision*> collisions)
{
	this->collisions = collisions;
}

CollisionsController::~CollisionsController()
{
	if (!collisions.empty())
	{
		collisions.clear();
	}
}

int CollisionsController::GetSize()
{
	return collisions.size();
}

ICollision* CollisionsController::GetCollisionByTitle(std::string root_title)
{
	for (ICollision*& collision : collisions)
	{
		if (collision->GetRootTitle() == root_title)
		{
			return collision;
		}
	}
	return nullptr;
}

std::vector<ICollision*> CollisionsController::GetCollisionsByTitle(std::string root_title)
{
	if (!CountCollisionsWithTitle(root_title)) {
		return std::vector<ICollision*>();
	}

	std::vector<ICollision*> temp;
	for (ICollision*& collision : collisions)
	{
		if (collision->GetRootTitle() == root_title)
		{
			temp.push_back(collision);
		}
	}
	return temp;
}

std::vector<ICollision*> CollisionsController::GetCollisionByType(std::string type)
{
	if (!CountCollisionsWithType(type)) {
		return std::vector<ICollision*>();
	}

	std::vector<ICollision*> temp;
	for (ICollision*& collision : collisions)
	{
		if (collision->GetType() == type)
		{
			temp.push_back(collision);
		}
	}
	return temp;
}

int CollisionsController::CountCollisionsWithTitle(std::string root_title)
{
	int count = 0;
	for (ICollision*& collision : collisions)
	{
		if (collision->GetRootTitle() == root_title)
		{
			count++;
		}
	}
	return count;
}

int CollisionsController::CountCollisionsWithType(std::string type)
{
	int count = 0;
	for (ICollision*& collision : collisions)
	{
		if (collision->GetType() == type)
		{
			count++;
		}
	}
	return count;
}

void CollisionsController::PushCollision(ICollision* collision)
{
	collisions.push_back(collision);
}

ICollision* CollisionsController::operator[](int index)
{
	if (index >= 0 && index < collisions.size())
	{
		return collisions[index];
	}
	return nullptr;
}
