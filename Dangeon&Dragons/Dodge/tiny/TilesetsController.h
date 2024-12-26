#pragma once
#include "TinyXml.h"

#include "Tileset.h"

#include <boost/container/vector.hpp>

class TilesetsController
{
	boost::container::vector<Tileset*> tilesets;
public:
	TilesetsController();
	TilesetsController(boost::container::vector<Tileset*> tilesets);
	TilesetsController(tinyxml2::XMLElement* element, std::string path);
	~TilesetsController();

	static void LoadTilesets(tinyxml2::XMLElement* element, boost::container::vector<Tileset*>& tilesets, std::string path);
	static Tileset* LoadTileset(int firstgId, const char* path);

	int GetSize();

	Tileset* GetTilesetByTileId(int tileId);

	Tileset* operator[](int index);
	Tileset* operator[](const char* name);
};