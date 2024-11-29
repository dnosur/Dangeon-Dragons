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

	ICollision* GetCollisionByTitle(char* root_title);

	std::vector<ICollision*> GetCollisionsByTitle(char* root_title);

	std::vector<ICollision*> GetCollisionByType(char* type);

	int CountCollisionsWithTitle(char* root_title);

	int CountCollisionsWithType(char* type);

	void PushCollision(ICollision* collision);

	ICollision* operator[](int index);
};