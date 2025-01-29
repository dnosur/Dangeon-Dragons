#include "PoligonCollisionsController.h"

PoligonCollisionsController::PoligonCollisionsController()
{

}

PoligonCollisionsController::PoligonCollisionsController(std::vector<PoligonCollision> collisions)
{
	this->collisions = collisions;
}

PoligonCollisionsController::~PoligonCollisionsController()
{
	if (!collisions.empty())
	{
		collisions.clear();
	}
}

int PoligonCollisionsController::GetSize()
{
	return collisions.size();
}

PoligonCollision* PoligonCollisionsController::GetCollisionByTitle(char* root_title)
{
	for (PoligonCollision& collision : collisions)
	{
		if (collision.GetRootTitle() == root_title)
		{
			return &collision;
		}
	}
	return nullptr;
}

PoligonCollision* PoligonCollisionsController::GetCollisionsByTitle(char* root_title)
{
	int max_count = CountCollisionsWithTitle(root_title);
	PoligonCollision* temp = new PoligonCollision[max_count];
	int index = 0;
	for (PoligonCollision& collision : collisions)
	{
		if (index >= max_count || index < 0) {
			return temp;
		}

		if (collision.GetRootTitle() == root_title)
		{
			temp[index] = collision;
			index++;
		}
	}
	return temp;
}

PoligonCollision* PoligonCollisionsController::GetCollisionByType(char* type)
{
	for (PoligonCollision& collision : collisions)
	{
		if (collision.GetType() == type)
		{
			return &collision;
		}
	}
	return nullptr;
}

PoligonCollision* PoligonCollisionsController::GetCollisionsByType(char* type)
{
	int max_count = CountCollisionsWithType(type);
	PoligonCollision* temp = new PoligonCollision[max_count];
	int index = 0;
	for (PoligonCollision& collision : collisions)
	{
		if (index >= max_count || index < 0) {
			return temp;
		}

		if (collision.GetType() == type)
		{
			temp[index] = collision;
			index++;
		}
	}
	return temp;
}

int PoligonCollisionsController::CountCollisionsWithTitle(char* root_title)
{
	int count = 0;
	for (PoligonCollision& collision : collisions)
	{
		if (collision.GetRootTitle() == root_title)
		{
			count++;
		}
	}
	return count;
}

int PoligonCollisionsController::CountCollisionsWithType(char* type)
{
	int count = 0;
	for (PoligonCollision& collision : collisions)
	{
		if (collision.GetType() == type)
		{
			count++;
		}
	}
	return count;
}

PoligonCollision* PoligonCollisionsController::operator[](int index)
{
	if (index >= 0 && index < collisions.size())
	{
		return &collisions[index];
	}
	return nullptr;
}
