#include "TileMap.h"

TileMap::TileMap()
{
	size = Size(0, 0);
	title = nullptr;

	undefined = true;
}

TileMap::TileMap(
	const char* title, Size size, Size tileSize, 
	char* orientation, char* renderOreder, int infinite, 
	int nextLayerId, int nextObjectId, 
	TilesetsController tilesetsController, 
	TinyClassController classesController, 
	TinySrpiteLayersController spriteLayersController
)
{
	copyStr(title, this->title);

	this->size = size;
	this->tileSize = tileSize;

	copyStr(orientation, this->orientation);
	copyStr(renderOreder, this->renderOreder);

	this->infinite = infinite;
	this->nextLayerId = nextLayerId;
	this->nextObjectId = nextObjectId;

	this->tilesetsController = tilesetsController;
	this->classesController = classesController;
	this->spriteLayersController = spriteLayersController;
}

bool TileMap::operator==(const TileMap& other) const
{
	return !strcmp(this->title, other.title) && other.undefined == undefined;
}

bool TileMap::operator!=(const TileMap& other) const
{
	return !(*this == other);
}

TileMap& TileMap::operator=(const TileMap& other)
{
	if (this != &other)
	{
		copyStr(other.title, title);

		size = other.size;
		tileSize = other.tileSize;

		copyStr(other.orientation, orientation);
		copyStr(other.renderOreder, renderOreder);

		infinite = other.infinite;
		nextLayerId = other.nextLayerId;
		nextObjectId = other.nextObjectId;

		tilesetsController = other.tilesetsController;
		classesController = other.classesController;
		spriteLayersController = other.spriteLayersController;

		undefined = other.undefined;
	}
	return *this;
}
