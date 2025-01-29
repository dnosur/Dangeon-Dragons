#include "Tileset.h"

Tileset::Tileset()
{
	firstgId = 0;
	lastgId = 0;
	tileWidth = 0;
	tileHeight = 0;
	tileCount = 0;
	columns = 0;
}

Tileset::Tileset(
	int firstgId, int tileWidth, int tileHeight, int width, int height,
	int tileCount, int columns, char* name, char* source,
	Image image, std::vector<Tile> tiles, TilesetPropertiesController tilesetProperties
){
	std::cout << source << std::endl;

	this->firstgId = firstgId;
	this->lastgId = firstgId + tileCount - 1;

	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;

	this->width = width;
	this->height = height;

	this->tileCount = tileCount;
	this->columns = columns;

	this->image = image;

	this->name = name;
	this->source = source;

	this->tiles = tiles;

	this->tilesetProperties = tilesetProperties;
}

Tileset::Tileset(
	int firstgId, int tileWidth, int tileHeight, int width, int height,
	int tileCount, int columns, std::string name,std::string source,
	Image image, std::vector<Tile> tiles, TilesetPropertiesController tilesetProperties
) {
	std::cout << source << std::endl;

	this->firstgId = firstgId;
	this->lastgId = firstgId + tileCount - 1;

	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;

	this->width = width;
	this->height = height;

	this->tileCount = tileCount;
	this->columns = columns;

	this->image = image;

	this->name = name;
	this->source = source;

	this->tiles = tiles;

	this->tilesetProperties = tilesetProperties;
}

int Tileset::GetFirstgId()
{
	return firstgId;
}

int Tileset::GetLastgId()
{
	return lastgId;
}

int Tileset::GetTileWidth()
{
	return tileWidth;
}

int Tileset::GetTileHeight()
{
	return tileHeight;
}

int Tileset::GetWidth()
{
	return width;
}

int Tileset::GetHeight()
{
	return height;
}

int Tileset::GetTileCount()
{
	return tileCount;
}

int Tileset::GetColumns()
{
	return columns;
}

std::string Tileset::GetName()
{
	return name;
}

std::string Tileset::GetSource()
{
	return source;
}

Tile* Tileset::GetTileById(int id)
{
	for (Tile& tile : tiles) {
		if (tile.GetId() == id - firstgId) {
			return &tile;
		}
	}
	return nullptr;
}

Image Tileset::GetImage()
{
	return image;
}

bool Tileset::IsContains(int gId)
{
	return gId >= firstgId - 1 && gId <= lastgId - 1;
}

int Tileset::MathId(int tileId)
{
	if (!IsContains(tileId)) {
		return -1;
	}

	return tileId - firstgId;
}

TilesetPropertiesController* Tileset::GetProperties()
{
	return &tilesetProperties;
}

Tile* Tileset::operator[](int index)
{
	if (index < 0 || index >= tiles.size()) {
		return nullptr;
	}
	return &tiles[index];
}
