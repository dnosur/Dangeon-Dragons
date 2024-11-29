#pragma once
#include "../collisions/ICollision.h"

class Tile
{
	int id;
	ICollision* collision;
public:
	Tile();
	Tile(int id, ICollision* collision);

	int GetId();
	ICollision* GetCollision();

	bool Undefined();

	bool operator==(const Tile& other) const;
	bool operator!=(const Tile& other) const;

	Tile& operator=(const Tile& other);
};