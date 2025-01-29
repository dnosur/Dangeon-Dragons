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

<<<<<<< Updated upstream
	static void LoadTilesets(tinyxml2::XMLElement* element, std::vector<Tileset*>& tilesets, std::string path);
	static Tileset* LoadTileset(int firstgId, const char* path);
=======
	static void LoadTilesets(
		tinyxml2::XMLElement* element, 
		std::vector<std::shared_ptr<Tileset>>& tilesets, 
		std::string path
	);
	static std::shared_ptr<Tileset> LoadTileset(int firstgId, std::string path);
>>>>>>> Stashed changes

	int GetSize();

	Tileset* GetTilesetByTileId(int tileId);

<<<<<<< Updated upstream
	Tileset* operator[](int index);
	Tileset* operator[](const char* name);
=======
	std::weak_ptr<Tileset> operator[](int index);
	std::weak_ptr<Tileset> operator[](std::string name);
>>>>>>> Stashed changes
};