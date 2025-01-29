#pragma once
#include "TinySrpiteLayersController.h"


class TilesetsController;
class TinyClassController;

#include "TilesetsController.h"
#include "TinyClassController.h"

struct TileMap
{
	Size size;
	Size tileSize;

	std::string orientation;
	std::string renderOreder;

	int infinite;

	int nextLayerId;
	int nextObjectId;

	std::string title;

	TilesetsController tilesetsController;
	TinyClassController classesController;
	TinySrpiteLayersController spriteLayersController;

	bool undefined;

	TileMap();
	TileMap(
		std::string title, Size size, Size tileSize,
		std::string orientation, std::string renderOreder,
		int infinite,
		int nextLayerId, int nextObjectId,
		TilesetsController tilesetsController,
		TinyClassController classesController,
		TinySrpiteLayersController spriteLayersController
	);

	bool operator==(const TileMap& other) const;
	bool operator!=(const TileMap& other) const;
	TileMap& operator=(const TileMap& other);
};