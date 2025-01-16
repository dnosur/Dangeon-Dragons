#pragma once
#include "TinyXml.h"

#include "Tileset.h"

class TilesetsController
{
	std::vector<Tileset*> tilesets;
public:
	TilesetsController();
	TilesetsController(std::vector<Tileset*> tilesets);
	TilesetsController(tinyxml2::XMLElement* element, std::string path);
	~TilesetsController();

	static void LoadTilesets(tinyxml2::XMLElement* element, std::vector<Tileset*>& tilesets, std::string path);
	static Tileset* LoadTileset(int firstgId, const char* path);

	int GetSize();

	Tileset* GetTilesetByTileId(int tileId);

	Tileset* operator[](int index);
	Tileset* operator[](const char* name);
};