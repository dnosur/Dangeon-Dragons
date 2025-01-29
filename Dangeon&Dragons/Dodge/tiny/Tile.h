#pragma once
#include "../collisions/ICollision.h"
#include "Animation/Animation.h"

#include "TilesetProperties/TilesetPropertiesController.h"

class Tile
{
	int id;
	std::shared_ptr<ICollision> collision;
	std::shared_ptr<Animation> animation;

	TilesetPropertiesController tilesetProperties;
public:
	Tile();
	Tile(int id, std::shared_ptr<ICollision> collision, std::shared_ptr<Animation> animation = nullptr);

	int GetId();
	std::weak_ptr<ICollision> GetCollision();
	std::weak_ptr<Animation> GetAnimation();

	TilesetPropertiesController* GetTilesetProperties();
	void SetTilesetProperties(TilesetPropertiesController tilesetProperties);

	bool Undefined();

	bool operator==(const Tile& other) const;
	bool operator!=(const Tile& other) const;

	Tile& operator=(const Tile& other);
};