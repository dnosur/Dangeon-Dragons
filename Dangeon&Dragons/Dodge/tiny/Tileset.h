#pragma once
#include "Tile.h"
#include "TilesetProperties/TilesetPropertiesController.h"

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
	std::vector<Tile> tiles;
	TilesetPropertiesController tilesetProperties;
public:
	Tileset();
	Tileset(
		int firstgId, int tileWidth, int tileHeight, int width, int height,
		int tileCount, int columns, char* name, char* source, 
		Image image, std::vector<Tile> tile, TilesetPropertiesController tilesetProperties
	);

	Tileset(
		int firstgId, int tileWidth, int tileHeight, int width, int height,
		int tileCount, int columns, std::string name, std::string source,
		Image image, std::vector<Tile> tile, TilesetPropertiesController tilesetProperties
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

	Tile* GetTileById(int id);

	Image GetImage();

	bool IsContains(int gId);
	int MathId(int tileId);

	TilesetPropertiesController* GetProperties();

	Tile* operator[](int index);
};

