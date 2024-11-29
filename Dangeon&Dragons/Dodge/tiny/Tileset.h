#pragma once
#include "Tile.h"

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

	char* name;
	char* source;

	Image image;
	std::vector<Tile> tiles;


public:
	Tileset();
	Tileset(
		int firstgId, int tileWidth, int tileHeight, int width, int height,
		int tileCount, int columns, char* name, char* source, 
		Image image, std::vector<Tile> tile
	);

	Tileset(
		int firstgId, int tileWidth, int tileHeight, int width, int height,
		int tileCount, int columns, const char* name, const char* source,
		Image image, std::vector<Tile> tile
	);
	~Tileset();

	int GetFirstgId();
	int GetLastgId();

	int GetTileWidth();
	int GetTileHeight();

	int GetWidth();
	int GetHeight();

	int GetTileCount();
	int GetColumns();

	char* GetName();
	char* GetSource();

	Tile* GetTileById(int id);

	Image GetImage();

	bool IsContains(int gId);
	int MathId(int tileId);

	Tile* operator[](int index);
};

