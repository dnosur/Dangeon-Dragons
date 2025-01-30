#pragma once
#include "Tile.h"
#include "TilesetProperties/TilesetPropertiesController.h"

#include <unordered_map>

class Tileset
{
	int firstgId;
	int lastgId;

	int tileWidth;
	int tileHeight;
	int tileCount;
	int columns;

	int width;
	int height;

	std::string name;
	std::string source;

	Image image;
	std::unordered_map<int, std::shared_ptr<Tile>> tiles;
	TilesetPropertiesController tilesetProperties;
public:
	Tileset();
	Tileset(
		int firstgId, int tileWidth, int tileHeight, int width, int height,
		int tileCount, int columns, char* name, char* source, 
		Image image, std::unordered_map<int, std::shared_ptr<Tile>> tiles, TilesetPropertiesController tilesetProperties
	);

	Tileset(
		int firstgId, int tileWidth, int tileHeight, int width, int height,
		int tileCount, int columns, std::string name, std::string source,
		Image image, std::unordered_map<int, std::shared_ptr<Tile>> tiles, TilesetPropertiesController tilesetProperties
	);

	int GetFirstgId();
	int GetLastgId();

	int GetTileWidth();
	int GetTileHeight();

	int GetWidth();
	int GetHeight();

	int GetTileCount();
	int GetColumns();

	std::string GetName();
	std::string GetSource();

	std::weak_ptr<Tile> GetTileById(int id);

	Image GetImage();

	bool IsContains(int gId);
	int MathId(int tileId);

	TilesetPropertiesController* GetProperties();

	std::weak_ptr<Tile> operator[](int index);
};

