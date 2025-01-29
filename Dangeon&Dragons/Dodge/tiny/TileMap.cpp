#include "TileMap.h"

TileMap::TileMap()
{
	size = Size(0, 0);

	undefined = true;
}

TileMap::TileMap(
	std::string title, Size size, Size tileSize, 
	std::string orientation, std::string renderOreder, int infinite,
	int nextLayerId, int nextObjectId, 
	TilesetsController tilesetsController, 
	TinyClassController classesController, 
	TinySrpiteLayersController spriteLayersController
)
{
	this->title = title;

	this->size = size;
	this->tileSize = tileSize;

	this->orientation = orientation;
	this->renderOreder = renderOreder;

	this->infinite = infinite;
	this->nextLayerId = nextLayerId;
	this->nextObjectId = nextObjectId;

	this->tilesetsController = tilesetsController;
	this->classesController = classesController;
	this->spriteLayersController = spriteLayersController;
}

bool TileMap::operator==(const TileMap& other) const
{
	return title == other.title && other.undefined == undefined;
}

bool TileMap::operator!=(const TileMap& other) const
{
	return !(*this == other);
}

TileMap& TileMap::operator=(const TileMap& other)
{
	if (this != &other)
	{
		title = other.title;

		size = other.size;
		tileSize = other.tileSize;

		orientation = other.orientation;
		renderOreder = other.renderOreder;

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
