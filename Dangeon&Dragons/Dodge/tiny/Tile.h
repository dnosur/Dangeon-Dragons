#pragma once
#include "../collisions/ICollision.h"
#include "Animation/Animation.h"

#include "TilesetProperties/TilesetPropertiesController.h"

class Tile
{
	int id;
	ICollision* collision;
	Animation* animation;

	TilesetPropertiesController tilesetProperties;
public:
	Tile();
	Tile(int id, ICollision* collision, Animation* animation = nullptr);

	int GetId();
	ICollision* GetCollision();
	Animation* GetAnimation();

	TilesetPropertiesController* GetTilesetProperties();
	void SetTilesetProperties(TilesetPropertiesController tilesetProperties);

	bool Undefined();

	bool operator==(const Tile& other) const;
	bool operator!=(const Tile& other) const;

	Tile& operator=(const Tile& other);
};