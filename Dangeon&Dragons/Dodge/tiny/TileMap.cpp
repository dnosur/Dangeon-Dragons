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
<<<<<<< Updated upstream
	copyStr(title, this->title);
=======
	this->title = title;
>>>>>>> Stashed changes

	this->size = size;
	this->tileSize = tileSize;

<<<<<<< Updated upstream
	copyStr(orientation, this->orientation);
	copyStr(renderOreder, this->renderOreder);
=======
	this->orientation = orientation;
	this->renderOreder = renderOreder;
>>>>>>> Stashed changes

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
<<<<<<< Updated upstream
		copyStr(other.title, title);
=======
		title = other.title;
>>>>>>> Stashed changes

		size = other.size;
		tileSize = other.tileSize;

<<<<<<< Updated upstream
		copyStr(other.orientation, orientation);
		copyStr(other.renderOreder, renderOreder);
=======
		orientation = other.orientation;
		renderOreder = other.renderOreder;
>>>>>>> Stashed changes

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
