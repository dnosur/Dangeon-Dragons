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
	Image image, std::unordered_map<int, std::shared_ptr<Tile>> tiles, TilesetPropertiesController tilesetProperties
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
	Image image, std::unordered_map<int, std::shared_ptr<Tile>> tiles, TilesetPropertiesController tilesetProperties
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

std::weak_ptr<Tile> Tileset::GetTileById(int id)
{
	auto it = tiles.find(id - firstgId);
	if (it == tiles.end()) {
		return {};
	}
	return it->second;
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

std::weak_ptr<Tile> Tileset::operator[](int index)
{
	if (index < 0 || index >= tiles.size()) {
		return {};
	}

	auto it = tiles.begin();
	std::advance(it, index);
	return it->second;
}
