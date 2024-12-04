#pragma once
#include "../collisions/ICollision.h"
#include "Animation/Animation.h"

class Tile
{
	int id;
	ICollision* collision;
	Animation* animation;
public:
	Tile();
	Tile(int id, ICollision* collision, Animation* animation = nullptr);

	int GetId();
	ICollision* GetCollision();
	Animation* GetAnimation();

	bool Undefined();

	bool operator==(const Tile& other) const;
	bool operator!=(const Tile& other) const;

	Tile& operator=(const Tile& other);
};