#pragma once
#include "PoligonCollision.h"

class PoligonCollisionsController
{
	std::vector<PoligonCollision> collisions;
public:
	PoligonCollisionsController();
	PoligonCollisionsController(std::vector<PoligonCollision> collisions);
	~PoligonCollisionsController();

	int GetSize();

	PoligonCollision* GetCollisionByTitle(char* root_title);

	PoligonCollision* GetCollisionsByTitle(char* root_title);

	PoligonCollision* GetCollisionByType(char* type);

	PoligonCollision* GetCollisionsByType(char* type);

	int CountCollisionsWithTitle(char* root_title);

	int CountCollisionsWithType(char* type);

	PoligonCollision* operator[](int index);
};