#pragma once
#include "ICollision.h"

__interface ICollision;
__interface IGameObject;

class CollisionsController
{
	std::vector<ICollision*> collisions;
public:
	CollisionsController();
	CollisionsController(std::vector<ICollision*> collisions);
	~CollisionsController();

	int GetSize();

	ICollision* GetCollisionByTitle(std::string root_title);

	std::vector<ICollision*> GetCollisionsByTitle(std::string root_title);

	std::vector<ICollision*> GetCollisionByType(std::string type);

	int CountCollisionsWithTitle(std::string root_title);

	int CountCollisionsWithType(std::string type);

	void PushCollision(ICollision* collision);

	ICollision* operator[](int index);
};