#pragma once
#include "TinyXml.h"

#include "Tileset.h"

class TilesetsController
{
	std::vector<std::shared_ptr<Tileset>> tilesets;
public:
	TilesetsController();
	TilesetsController(std::vector<std::shared_ptr<Tileset>> tilesets);
	TilesetsController(tinyxml2::XMLElement* element, std::string path);
	~TilesetsController();

	static void LoadTilesets(
		tinyxml2::XMLElement* element, 
		std::vector<std::shared_ptr<Tileset>>& tilesets, 
		std::string path
	);
	static std::shared_ptr<Tileset> LoadTileset(int firstgId, const char* path);

	int GetSize();

	std::weak_ptr<Tileset> GetTilesetByTileId(int tileId);

	std::weak_ptr<Tileset> operator[](int index);
	std::weak_ptr<Tileset> operator[](const char* name);
};