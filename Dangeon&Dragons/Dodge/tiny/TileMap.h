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

	char* orientation;
	char* renderOreder;

	int infinite;

	int nextLayerId;
	int nextObjectId;

	char* title;

	TilesetsController tilesetsController;
	TinyClassController classesController;
	TinySrpiteLayersController spriteLayersController;

	bool undefined;

	TileMap();
	TileMap(
		const char* title, Size size, Size tileSize,
		char* orientation, char* renderOreder,
		int infinite,
		int nextLayerId, int nextObjectId,
		TilesetsController tilesetsController,
		TinyClassController classesController,
		TinySrpiteLayersController spriteLayersController
	);
	~TileMap();

	bool operator==(const TileMap& other) const;
	bool operator!=(const TileMap& other) const;
	TileMap& operator=(const TileMap& other);
};